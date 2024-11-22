/*
 * Copyright (c) 2014, Kevin Läufer
 * Copyright (c) 2014-2017, Niklas Hauser
 * Copyright (c) 2020, Mike Wolfram
 * Copyright (c) 2021, Raphael Lehmann
 * Copyright (c) 2021-2023, Christopher Durand
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#ifndef MODM_STM32_DMA_HPP
#define MODM_STM32_DMA_HPP

#include <cstdint>
#include <algorithm>
#include <array>
#include "../device.hpp"
#include "dma_hal.hpp"

namespace modm
{

namespace platform
{

/// @cond
namespace dma
{
	template <typename ChannelT, Peripheral peripheral, DmaBase::Signal signal>
	struct RequestMapping;
}
/// @endcond
/**
 * DMA controller
 *
 * Does not support - among other things - double buffering or FIFO usage
 *
 * @author	Mike Wolfram
 * @ingroup	modm_platform_dma
 */
template <uint32_t ID>
class DmaController : public DmaBase
{
	static_assert(ID >= 1 and ID <= 2, "invalid DMA controller ID");

public:
	/**
	 * Enable the DMA controller in the RCC
	 */
	static void
	enable()
	{
		if constexpr (ID == 1)
			Rcc::enable<Peripheral::Dma1>();
		else {
			Rcc::enable<Peripheral::Dma2>();
		}
		Rcc::enable<Peripheral::Dmamux1>();
	}
	/**
	 * Disable the DMA controller in the RCC
	 */
	static void
	disable()
	{
		if constexpr (ID == 1)
			Rcc::disable<Peripheral::Dma1>();
		else
			Rcc::disable<Peripheral::Dma2>();
	}

	/**
	 * Class representing a DMA channel/stream
	 */
	template <DmaBase::Channel ChannelID>
	class Channel : public DmaBase
	{
		static_assert(
				(ID == 1 and
						ChannelID >= DmaBase::Channel::Channel1 and
						ChannelID <= DmaBase::Channel::Channel6)
				or
				(ID == 2 and
						ChannelID >= DmaBase::Channel::Channel1 and
						ChannelID <= DmaBase::Channel::Channel6)
				, "invalid Channel ID for that DMA controller"
				);

		using ControlHal = DmaHal<ID>;

		static constexpr uint32_t CHANNEL_BASE { ControlHal::CHANNEL_BASE +
			uint32_t(ChannelID) * ControlHal::CHANNEL_2_CHANNEL };

		using ChannelHal = DmaChannelHal<ChannelID, CHANNEL_BASE>;

	public:
		/**
		 * Configure the DMA channel
		 *
		 * Stops the DMA channel and writes the new values to its control register.
		 *
		 * @param[in] direction Direction of the DMA channel
		 * @param[in] memoryDataSize Size of data in memory (byte, halfword, word)
		 * @param[in] peripheralDataSize Size of data in peripheral (byte, halfword, word)
		 * @param[in] memoryIncrement Defines whether the memory address is incremented
		 * 			  after a transfer completed
		 * @param[in] peripheralIncrement Defines whether the peripheral address is
		 * 			  incremented after a transfer completed
		 * @param[in] priority Priority of the DMA channel
		 * @param[in] circularMode Transfer data in circular mode?
		 */
		static void
		configure(DataTransferDirection direction, MemoryDataSize memoryDataSize,
				PeripheralDataSize peripheralDataSize,
				MemoryIncrementMode memoryIncrement,
				PeripheralIncrementMode peripheralIncrement,
				Priority priority = Priority::Medium,
				CircularMode circularMode = CircularMode::Disabled)
		{
			ChannelHal::configure(direction, memoryDataSize, peripheralDataSize,
					memoryIncrement, peripheralIncrement, priority, circularMode);
		}

		/**
		 * Start the transfer of the DMA channel and clear all interrupt flags.
		 */
		static void
		start()
		{
			ControlHal::clearInterruptFlags(InterruptFlags::All, ChannelID);
			ChannelHal::start();
		}

		/**
		 * Stop a DMA channel transfer
		 */
		static void
		stop()
		{
			ChannelHal::stop();
		}

		/**
		 * Get the direction of the data transfer
		 */
		static DataTransferDirection
		getDataTransferDirection()
		{
			return ChannelHal::getDataTransferDirection();
		}

		/**
		 * Set the memory address of the DMA channel
		 *
		 * @note In Mem2Mem mode use this method to set the memory source address.
		 *
		 * @param[in] address Source address
		 */
		static void
		setMemoryAddress(uintptr_t address)
		{
			ChannelHal::setMemoryAddress(address);
		}
		/**
		 * Set the peripheral address of the DMA channel
		 *
		 * @note In Mem2Mem mode use this method to set the memory destination address.
		 *
		 * @param[in] address Destination address
		 */
		static void
		setPeripheralAddress(uintptr_t address)
		{
			ChannelHal::setPeripheralAddress(address);
		}

		/**
		 * Enable/disable memory increment
		 *
		 * When enabled, the memory address is incremented by the size of the data
		 * (e.g. 1 for byte transfers, 4 for word transfers) after the transfer
		 * completed.
		 *
		 * @param[in] increment Enable/disable
		 */
		static void
		setMemoryIncrementMode(bool increment)
		{
			ChannelHal::setMemoryIncrementMode(increment);
		}
		/**
		 * Enable/disable peripheral increment
		 *
		 * When enabled, the peripheral address is incremented by the size of the data
		 * (e.g. 1 for byte transfers, 4 for word transfers) after the transfer
		 * completed.
		 *
		 * @param[in] increment Enable/disable
		 */
		static void
		setPeripheralIncrementMode(bool increment)
		{
			ChannelHal::setPeripheralIncrementMode(increment);
		}

		/**
		 * Set the length of data to be transfered
		 */
		static void
		setDataLength(std::size_t length)
		{
			ChannelHal::setDataLength(length);
		}

		/**
		 * Set the IRQ handler for transfer errors
		 *
		 * The handler will be called from the channels IRQ handler function
		 * when the IRQ status indicates an error occured.
		 */
		static void
		setTransferErrorIrqHandler(IrqHandler irqHandler)
		{
			transferError = irqHandler;
		}
		/**
		 * Set the IRQ handler for half transfer complete
		 *
		 * Called by the channels IRQ handler when the transfer is half complete.
		 */
		static void
		setHalfTransferCompleteIrqHandler(IrqHandler irqHandler)
		{
			halfTransferComplete = irqHandler;
		}
		/**
		 * Set the IRQ handler for transfer complete
		 *
		 * Called by the channels IRQ handler when the transfer is complete.
		 */
		static void
		setTransferCompleteIrqHandler(IrqHandler irqHandler)
		{
			transferComplete = irqHandler;
		}

		/**
		 * Set the peripheral that operates the channel
		 */
		template <DmaBase::Request dmaRequest>
		static void
		setPeripheralRequest()
		{
			constexpr auto muxChannel = std::find_if(muxChannels.begin(), muxChannels.end(), [](MuxChannel ch) {
				return (ch.dmaInstance == ID) && (ch.dmaChannel == (uint32_t(ChannelID) + 1));
			})->muxChannel;
			auto* channel = DMAMUX1_Channel0 + muxChannel;
			channel->CCR = (channel->CCR & ~DMAMUX_CxCR_DMAREQ_ID) | uint32_t(dmaRequest);
		}

		/**
		 * IRQ handler of the DMA channel
		 *
		 * Reads the IRQ status and checks for error or transfer complete. In case
		 * of error the DMA channel will be disabled.
		 */
		modm_always_inline static void
		interruptHandler()
		{
			static const uint32_t HT_Flag {
				uint32_t(InterruptFlags::HalfTransferComplete) << (uint32_t(ChannelID) * 4)
			};
			static const uint32_t TC_Flag {
				uint32_t(InterruptFlags::TransferComplete) << (uint32_t(ChannelID) * 4)
			};
			static const uint32_t TE_Flag {
				uint32_t(InterruptFlags::Error) << (uint32_t(ChannelID) * 4)
			};
			auto isr { ControlHal::getInterruptFlags() };
			if (isr & TE_Flag) {
				disable();
				if (transferError)
					transferError();
			}
			if (halfTransferComplete and (isr & HT_Flag)) {
				halfTransferComplete();
			}
			if (transferComplete and (isr & TC_Flag)) {
				transferComplete();
			}

			ControlHal::clearInterruptFlags(InterruptFlags::Global, ChannelID);
		}

		/**
		 * Read channel status flags when channel interrupts are disabled.
		 * This function is useful to query the transfer state when the use of
		 * the channel interrupt is not required for the application.
		 *
		 * @warning Flags are automatically cleared in the ISR if the channel
		 * 			interrupt is enabled or when start() is called.
		 */
		static InterruptFlags_t
		getInterruptFlags()
		{
			const auto globalFlags = ControlHal::getInterruptFlags();
			const auto mask = static_cast<uint8_t>(InterruptFlags::All);
			const auto shift = static_cast<uint32_t>(ChannelID) * 4;
			const auto channelFlags = static_cast<uint8_t>((globalFlags >> shift) & mask);
			return InterruptFlags_t{channelFlags};
		}

		/**
		 * Clear channel interrupt flags.
		 * Use only when the channel interrupt is disabled.
		 *
		 * @warning Flags are automatically cleared in the ISR if the channel
		 * 			interrupt is enabled or when start() is called.
		 */
		static void
		clearInterruptFlags(InterruptFlags_t flags = InterruptFlags::All)
		{
			ControlHal::clearInterruptFlags(InterruptFlags(flags.value), ChannelID);
		}

		/**
		 * Enable the IRQ vector of the channel
		 *
		 * @param[in] priority Priority of the IRQ
		 */
		static void
		enableInterruptVector(uint32_t priority = 1)
		{
			NVIC_SetPriority(DmaBase::Nvic<ID>::DmaIrqs[uint32_t(ChannelID)], priority);
			NVIC_EnableIRQ(DmaBase::Nvic<ID>::DmaIrqs[uint32_t(ChannelID)]);
		}
		/**
		 * Disable the IRQ vector of the channel
		 */
		static void
		disableInterruptVector()
		{
			NVIC_DisableIRQ(DmaBase::Nvic<ID>::DmaIrqs[uint32_t(ChannelID)]);
		}

		/**
		 * Enable the specified interrupt of the channel
		 */
		static void
		enableInterrupt(InterruptEnable_t irq)
		{
			ChannelHal::enableInterrupt(irq);
		}
		/**
		 * Disable the specified interrupt of the channel
		 */
		static void
		disableInterrupt(InterruptEnable_t irq)
		{
			ChannelHal::disableInterrupt(irq);
		}

		/**
		 * Helper to verify that the selected channel supports the selected
		 * hardware and provides the Request to be set in setPeripheralRequest().
		 */
		template <Peripheral peripheral, Signal signal = Signal::NoSignal>
		using RequestMapping = dma::RequestMapping<Channel, peripheral, signal>;
	private:
		static inline DmaBase::IrqHandler transferError { nullptr };
		static inline DmaBase::IrqHandler halfTransferComplete { nullptr };
		static inline DmaBase::IrqHandler transferComplete { nullptr };

		struct MuxChannel
		{
			uint8_t muxChannel;
			uint8_t dmaInstance;
			uint8_t dmaChannel;
		};

		static constexpr std::array muxChannels = {
			MuxChannel(0, 1, 1),
			MuxChannel(1, 1, 2),
			MuxChannel(2, 1, 3),
			MuxChannel(3, 1, 4),
			MuxChannel(4, 1, 5),
			MuxChannel(5, 1, 6),
			MuxChannel(6, 2, 1),
			MuxChannel(7, 2, 2),
			MuxChannel(8, 2, 3),
			MuxChannel(9, 2, 4),
			MuxChannel(10, 2, 5),
			MuxChannel(11, 2, 6)
		};
	};
};

/// @ingroup	modm_platform_dma
/// @{

/*
 * Derive DMA controller classes for convenience. Every derived class defines
 * the channels available on that controller.
 */
class Dma1: public DmaController<1>
{
public:
	using Channel1 = DmaController<1>::Channel<DmaBase::Channel::Channel1>;
	using Channel2 = DmaController<1>::Channel<DmaBase::Channel::Channel2>;
	using Channel3 = DmaController<1>::Channel<DmaBase::Channel::Channel3>;
	using Channel4 = DmaController<1>::Channel<DmaBase::Channel::Channel4>;
	using Channel5 = DmaController<1>::Channel<DmaBase::Channel::Channel5>;
	using Channel6 = DmaController<1>::Channel<DmaBase::Channel::Channel6>;
};

class Dma2: public DmaController<2>
{
public:
	using Channel1 = DmaController<2>::Channel<DmaBase::Channel::Channel1>;
	using Channel2 = DmaController<2>::Channel<DmaBase::Channel::Channel2>;
	using Channel3 = DmaController<2>::Channel<DmaBase::Channel::Channel3>;
	using Channel4 = DmaController<2>::Channel<DmaBase::Channel::Channel4>;
	using Channel5 = DmaController<2>::Channel<DmaBase::Channel::Channel5>;
	using Channel6 = DmaController<2>::Channel<DmaBase::Channel::Channel6>;
};

/// @}

/// @cond
/*
 * Specialization of the RequestMapping. For all hardware supported by DMA the
 * RequestMapping structure defines the channel and the Request. It can be used
 * by hardware classes to verify that the provided channel is valid and to
 * get the value to set in setPeripheralRequest().
 *
 * Example:
 * template <class DmaRx, class DmaTx>
 * class SpiMaster1_Dma : public SpiMaster1
 * {
 *     using RxChannel = typename DmaRx::template RequestMapping<Peripheral::Spi1, DmaBase::Signal::Rx>::Channel;
 * 	   using TxChannel = typename DmaTx::template RequestMapping<Peripheral::Spi1, DmaBase::Signal::Tx>::Channel;
 * 	   static constexpr DmaBase::Request RxRequest = DmaRx::template RequestMapping<Peripheral::Spi1, DmaBase::Signal::Rx>::Request;
 * 	   static constexpr DmaBase::Request TxRequest = DmaTx::template RequestMapping<Peripheral::Spi1, DmaBase::Signal::Tx>::Request;
 *
 *     ...
 * };
 */
namespace dma
{

	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Dma1, DmaBase::Signal::Generator0>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request1;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Dma1, DmaBase::Signal::Generator1>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request2;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Dma1, DmaBase::Signal::Generator2>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request3;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Dma1, DmaBase::Signal::Generator3>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request4;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Adc1, DmaBase::Signal::NoSignal>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request5;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Dac1, DmaBase::Signal::Ch1>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request6;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Dac1, DmaBase::Signal::Ch2>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request7;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim6, DmaBase::Signal::Up>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request8;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim7, DmaBase::Signal::Up>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request9;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Spi1, DmaBase::Signal::Rx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request10;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Spi1, DmaBase::Signal::Tx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request11;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Spi2, DmaBase::Signal::Rx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request12;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Spi2, DmaBase::Signal::Tx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request13;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Spi3, DmaBase::Signal::Rx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request14;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Spi3, DmaBase::Signal::Tx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request15;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::I2c1, DmaBase::Signal::Rx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request16;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::I2c1, DmaBase::Signal::Tx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request17;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::I2c2, DmaBase::Signal::Rx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request18;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::I2c2, DmaBase::Signal::Tx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request19;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::I2c3, DmaBase::Signal::Rx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request20;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::I2c3, DmaBase::Signal::Tx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request21;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Usart1, DmaBase::Signal::Rx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request24;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Usart1, DmaBase::Signal::Tx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request25;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Usart2, DmaBase::Signal::Rx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request26;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Usart2, DmaBase::Signal::Tx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request27;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Lpuart1, DmaBase::Signal::Rx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request34;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Lpuart1, DmaBase::Signal::Tx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request35;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Adc2, DmaBase::Signal::NoSignal>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request36;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim1, DmaBase::Signal::Ch1>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request42;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim1, DmaBase::Signal::Ch2>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request43;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim1, DmaBase::Signal::Ch3>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request44;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim1, DmaBase::Signal::Ch4>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request45;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim1, DmaBase::Signal::Up>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request46;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim1, DmaBase::Signal::Trig>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request47;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim1, DmaBase::Signal::Com>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request48;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim8, DmaBase::Signal::Ch1>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request49;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim8, DmaBase::Signal::Ch2>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request50;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim8, DmaBase::Signal::Ch3>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request51;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim8, DmaBase::Signal::Ch4>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request52;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim8, DmaBase::Signal::Up>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request53;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim8, DmaBase::Signal::Trig>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request54;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim8, DmaBase::Signal::Com>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request55;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim2, DmaBase::Signal::Ch1>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request56;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim2, DmaBase::Signal::Ch2>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request57;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim2, DmaBase::Signal::Ch3>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request58;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim2, DmaBase::Signal::Ch4>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request59;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim2, DmaBase::Signal::Up>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request60;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim3, DmaBase::Signal::Ch1>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request61;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim3, DmaBase::Signal::Ch2>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request62;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim3, DmaBase::Signal::Ch3>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request63;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim3, DmaBase::Signal::Ch4>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request64;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim3, DmaBase::Signal::Up>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request65;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim3, DmaBase::Signal::Trig>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request66;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim4, DmaBase::Signal::Ch1>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request67;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim4, DmaBase::Signal::Ch2>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request68;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim4, DmaBase::Signal::Ch3>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request69;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim4, DmaBase::Signal::Ch4>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request70;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim4, DmaBase::Signal::Up>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request71;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim15, DmaBase::Signal::Ch1>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request78;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim15, DmaBase::Signal::Up>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request79;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim15, DmaBase::Signal::Trig>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request80;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim15, DmaBase::Signal::Com>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request81;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim16, DmaBase::Signal::Ch1>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request82;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim16, DmaBase::Signal::Up>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request83;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim17, DmaBase::Signal::Ch1>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request84;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Tim17, DmaBase::Signal::Up>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request85;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Dac3, DmaBase::Signal::Ch1>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request102;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Dac3, DmaBase::Signal::Ch2>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request103;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Sai1, DmaBase::Signal::A>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request108;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Sai1, DmaBase::Signal::B>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request109;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Fmac, DmaBase::Signal::Read>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request110;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Fmac, DmaBase::Signal::Write>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request111;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Cordic, DmaBase::Signal::Read>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request112;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Cordic, DmaBase::Signal::Write>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request113;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Ucpd1, DmaBase::Signal::Rx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request114;
	};
	template <typename ChannelT>
	struct RequestMapping<ChannelT, Peripheral::Ucpd1, DmaBase::Signal::Tx>
	{
		using Channel = ChannelT;
		static constexpr DmaBase::Request Request = DmaBase::Request::Request115;
	};
}
/// @endcond
}	// namespace platform

}	// namespace modm

#endif	// MODM_STM32_DMA_HPP