/*
 * Copyright (c) 2020, Mike Wolfram
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#ifndef MODM_STM32_SPI_MASTER3_DMA_HPP
#	error 	"Don't include this file directly, use 'spi_master_3_dma.hpp' instead!"
#endif

template <class DmaChannelRx, class DmaChannelTx>
template <class SystemClock, modm::baudrate_t baudrate, modm::percent_t tolerance>
void
modm::platform::SpiMaster3_Dma<DmaChannelRx, DmaChannelTx>::initialize()
{
	// Configure the DMA channels, then calls SpiMaster3::initialzie().
	Dma::RxChannel::configure(DmaBase::DataTransferDirection::PeripheralToMemory,
			DmaBase::MemoryDataSize::Byte, DmaBase::PeripheralDataSize::Byte,
			DmaBase::MemoryIncrementMode::Increment, DmaBase::PeripheralIncrementMode::Fixed,
			DmaBase::Priority::High);
	Dma::RxChannel::setPeripheralAddress(SPI3_BASE + 0x0c);
	Dma::RxChannel::setTransferErrorIrqHandler(handleDmaTransferError);
	Dma::RxChannel::setTransferCompleteIrqHandler(handleDmaReceiveComplete);
	Dma::RxChannel::enableInterruptVector();
	Dma::RxChannel::enableInterrupt(DmaBase::InterruptEnable::TransferError |
			DmaBase::InterruptEnable::TransferComplete);
	Dma::RxChannel::template setPeripheralRequest<Dma::RxRequest>();

	Dma::TxChannel::configure(DmaBase::DataTransferDirection::MemoryToPeripheral,
			DmaBase::MemoryDataSize::Byte, DmaBase::PeripheralDataSize::Byte,
			DmaBase::MemoryIncrementMode::Increment, DmaBase::PeripheralIncrementMode::Fixed,
			DmaBase::Priority::High);
	Dma::TxChannel::setPeripheralAddress(SPI3_BASE + 0x0c);
	Dma::TxChannel::setTransferErrorIrqHandler(handleDmaTransferError);
	Dma::TxChannel::setTransferCompleteIrqHandler(handleDmaTransmitComplete);
	Dma::TxChannel::enableInterruptVector();
	Dma::TxChannel::enableInterrupt(DmaBase::InterruptEnable::TransferError |
			DmaBase::InterruptEnable::TransferComplete);
	Dma::TxChannel::template setPeripheralRequest<Dma::TxRequest>();

	SpiMaster3::initialize<SystemClock, baudrate, tolerance>();

	SpiHal3::setRxFifoThreshold(SpiHal3::RxFifoThreshold::QuarterFull);
}

template <class DmaChannelRx, class DmaChannelTx>
modm::ResumableResult<uint8_t>
modm::platform::SpiMaster3_Dma<DmaChannelRx, DmaChannelTx>::transfer(uint8_t data)
{
	// this is a manually implemented "fast resumable function"
	// there is no context or nesting protection, since we don't need it.
	// there are only two states encoded into 1 bit (LSB of state):
	//   1. waiting to start, and
	//   2. waiting to finish.
	// LSB != Bit0 ?
	if ( !(state & Bit0) )
	{
		// disable DMA for single byte transfer
		SpiHal3::disableInterrupt(SpiBase::Interrupt::TxDmaEnable |
				SpiBase::Interrupt::RxDmaEnable);

		// wait for previous transfer to finish
		if (!SpiHal3::isTransmitRegisterEmpty())
			return {modm::rf::Running};

		// start transfer by copying data into register
		SpiHal3::write(data);

		// set LSB = Bit0
		state |= Bit0;
	}

	if (!SpiHal3::isReceiveRegisterNotEmpty())
		return {modm::rf::Running};

	SpiHal3::read(data);

	// transfer finished
	state &= ~Bit0;
	return {modm::rf::Stop, data};
}

template <class DmaChannelRx, class DmaChannelTx>
modm::ResumableResult<void>
modm::platform::SpiMaster3_Dma<DmaChannelRx, DmaChannelTx>::transfer(
		const uint8_t *tx, uint8_t *rx, std::size_t length)
{
	// this is a manually implemented "fast resumable function"
	// there is no context or nesting protection, since we don't need it.
	// there are only two states encoded into 1 bit (Bit1 of state):
	//   1. initialize index, and
	//   2. wait for 1-byte transfer to finish.

	// we are only interested in Bit1
	switch(state & Bit1)
	{
	case 0:
		// we will only visit this state once
		state |= Bit1;
		dmaError = false;
		SpiHal3::enableInterrupt(SpiBase::Interrupt::TxDmaEnable |
				SpiBase::Interrupt::RxDmaEnable);

		if (tx) {
			Dma::TxChannel::setMemoryAddress(uint32_t(tx));
			Dma::TxChannel::setMemoryIncrementMode(true);
		} else {
			Dma::TxChannel::setMemoryAddress(uint32_t(&dmaDummy));
			Dma::TxChannel::setMemoryIncrementMode(false);
		}
		if (rx) {
			Dma::RxChannel::setMemoryAddress(uint32_t(rx));
			Dma::RxChannel::setMemoryIncrementMode(true);
		} else {
			Dma::RxChannel::setMemoryAddress(uint32_t(&dmaDummy));
			Dma::RxChannel::setMemoryIncrementMode(false);
		}

		Dma::RxChannel::setDataLength(length);
		dmaReceiveComplete = false;
		Dma::RxChannel::start();

		Dma::TxChannel::setDataLength(length);
		dmaTransmitComplete = false;
		Dma::TxChannel::start();

		[[fallthrough]];

	default:
		if (not dmaError)
		{
			if (not dmaTransmitComplete and not dmaReceiveComplete)
				return { modm::rf::Running };
			if (SpiHal3::getInterruptFlags() & SpiBase::InterruptFlag::Busy)
				return { modm::rf::Running };
			if (SpiHal3::getInterruptFlags() & (SpiBase::InterruptFlag::FifoTxLevel |
													   SpiBase::InterruptFlag::FifoRxLevel))
				return { modm::rf::Running };
		}

		SpiHal3::disableInterrupt(SpiBase::Interrupt::TxDmaEnable |
				SpiBase::Interrupt::RxDmaEnable);
		// clear the state
		state &= ~Bit1;
		return {modm::rf::Stop};
	}
}

template <class DmaChannelRx, class DmaChannelTx>
void
modm::platform::SpiMaster3_Dma<DmaChannelRx, DmaChannelTx>::handleDmaTransferError()
{
	SpiHal3::disableInterrupt(SpiBase::Interrupt::TxDmaEnable |
			SpiBase::Interrupt::RxDmaEnable);
	Dma::RxChannel::stop();
	Dma::TxChannel::stop();
	dmaError = true;
}

template <class DmaChannelRx, class DmaChannelTx>
void
modm::platform::SpiMaster3_Dma<DmaChannelRx, DmaChannelTx>::handleDmaReceiveComplete()
{
	Dma::RxChannel::stop();
	dmaReceiveComplete = true;
}

template <class DmaChannelRx, class DmaChannelTx>
void
modm::platform::SpiMaster3_Dma<DmaChannelRx, DmaChannelTx>::handleDmaTransmitComplete()
{
	Dma::TxChannel::stop();
	dmaTransmitComplete = true;
}