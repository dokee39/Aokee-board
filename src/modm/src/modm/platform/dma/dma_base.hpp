/*
 * Copyright (c) 2014, Kevin Läufer
 * Copyright (c) 2014-2017, Niklas Hauser
 * Copyright (c) 2020, Mike Wolfram
 * Copyright (c) 2021, Raphael Lehmann
 * Copyright (c) 2021, Christopher Durand
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#ifndef MODM_STM32_DMA_BASE_HPP
#define MODM_STM32_DMA_BASE_HPP

#include <stdint.h>
#include <cstddef>

#include "../device.hpp"

#include <modm/architecture/interface/assert.hpp>
#include <modm/architecture/interface/interrupt.hpp>
#include <modm/architecture/interface/register.hpp>

namespace modm
{

namespace platform
{
/**
 * DMA
 *
 * @author	Kevin Laeufer
 * @author	Mike Wolfram
 * @ingroup	modm_platform_dma
 */
class DmaBase
{
public:
	// Enums
	enum class
	Channel
	{
		Channel1 = 0,
		Channel2,
		Channel3,
		Channel4,
		Channel5,
		Channel6,
	};

	enum class
	Request
	{
		None = 0,
		Request1,
		Request2,
		Request3,
		Request4,
		Request5,
		Request6,
		Request7,
		Request8,
		Request9,
		Request10,
		Request11,
		Request12,
		Request13,
		Request14,
		Request15,
		Request16,
		Request17,
		Request18,
		Request19,
		Request20,
		Request21,
		Request22,
		Request23,
		Request24,
		Request25,
		Request26,
		Request27,
		Request28,
		Request29,
		Request30,
		Request31,
		Request32,
		Request33,
		Request34,
		Request35,
		Request36,
		Request37,
		Request38,
		Request39,
		Request40,
		Request41,
		Request42,
		Request43,
		Request44,
		Request45,
		Request46,
		Request47,
		Request48,
		Request49,
		Request50,
		Request51,
		Request52,
		Request53,
		Request54,
		Request55,
		Request56,
		Request57,
		Request58,
		Request59,
		Request60,
		Request61,
		Request62,
		Request63,
		Request64,
		Request65,
		Request66,
		Request67,
		Request68,
		Request69,
		Request70,
		Request71,
		Request72,
		Request73,
		Request74,
		Request75,
		Request76,
		Request77,
		Request78,
		Request79,
		Request80,
		Request81,
		Request82,
		Request83,
		Request84,
		Request85,
		Request86,
		Request87,
		Request88,
		Request89,
		Request90,
		Request91,
		Request92,
		Request93,
		Request94,
		Request95,
		Request96,
		Request97,
		Request98,
		Request99,
		Request100,
		Request101,
		Request102,
		Request103,
		Request104,
		Request105,
		Request106,
		Request107,
		Request108,
		Request109,
		Request110,
		Request111,
		Request112,
		Request113,
		Request114,
		Request115,
	};
	enum class
	Priority : uint32_t
	{
		Low 		= 0,
		Medium  	= DMA_CCR_PL_0,
		High 		= DMA_CCR_PL_1,
		VeryHigh 	= DMA_CCR_PL_1 | DMA_CCR_PL_0,
	};

	/// In direct mode (if the FIFO is not used)
	/// MSIZE is forced by hardware to the same value as PSIZE
	enum class
	MemoryDataSize : uint32_t
	{
		Byte 		= 0,
		Bit8 		= Byte,
		HalfWord 	= DMA_CCR_MSIZE_0,
		Bit16 		= HalfWord,
		Word 		= DMA_CCR_MSIZE_1,
		Bit32 		= Word,
	};

	enum class
	PeripheralDataSize : uint32_t
	{
		Byte 		= 0,
		Bit8 		= Byte,
		HalfWord 	= DMA_CCR_PSIZE_0,
		Bit16 		= HalfWord,
		Word 		= DMA_CCR_PSIZE_1,
		Bit32 		= Word,
	};

	enum class
	MemoryIncrementMode : uint32_t
	{
		Fixed 		= 0,
		Increment 	= DMA_CCR_MINC, ///< incremented according to MemoryDataSize
	};

	enum class
	PeripheralIncrementMode : uint32_t
	{
		Fixed 		= 0,
		Increment 	= DMA_CCR_PINC, ///< incremented according to PeripheralDataSize
	};

	enum class
	CircularMode : uint32_t
	{
		Disabled 	= 0,
		Enabled 	= DMA_CCR_CIRC, ///< circular mode
	};

	enum class
	DataTransferDirection : uint32_t
	{
		/// Source: DMA_CPARx; Sink: DMA_CMARx
		PeripheralToMemory 	= 0,
		/// Source: DMA_CMARx; Sink: DMA_CPARx
		MemoryToPeripheral 	= DMA_CCR_DIR,
		/// Source: DMA_CPARx; Sink: DMA_CMARx
		MemoryToMemory 		= DMA_CCR_MEM2MEM,
	};

	/**
	 * Peripheral signals that can be used in DMA channels
	 */
	enum class
	Signal : uint8_t {
		NoSignal,
		A,
		B,
		Ch1,
		Ch2,
		Ch3,
		Ch4,
		Com,
		Generator0,
		Generator1,
		Generator2,
		Generator3,
		Read,
		Rx,
		Trig,
		Tx,
		Up,
		Write,
	};

	enum class InterruptEnable : uint32_t {
		TransferComplete	= DMA_CCR_TCIE,
		HalfTransfer		= DMA_CCR_HTIE,
		TransferError		= DMA_CCR_TEIE,
	};
	MODM_FLAGS32(InterruptEnable);

	enum class InterruptFlags : uint8_t {
		Global = 0b0001,
		TransferComplete = 0b0010,
		HalfTransferComplete = 0b0100,
		Error = 0b1000,
		All = 0b1111,
	};
	MODM_FLAGS32(InterruptFlags);
	using IrqHandler = void (*)(void);

protected:
	static constexpr uint32_t memoryMask =
			DMA_CCR_MSIZE_0  | DMA_CCR_MSIZE_1  |	// MemoryDataSize
			DMA_CCR_MINC                        |	// MemoryIncrementMode
			DMA_CCR_DIR      | DMA_CCR_MEM2MEM; 	// DataTransferDirection
	static constexpr uint32_t peripheralMask =
			DMA_CCR_PSIZE_0  | DMA_CCR_PSIZE_1  |	// PeripheralDataSize
			DMA_CCR_PINC                        |	// PeripheralIncrementMode
			DMA_CCR_DIR      | DMA_CCR_MEM2MEM;  	// DataTransferDirection
	static constexpr uint32_t configmask =
			DMA_CCR_CIRC     |						// CircularMode
			DMA_CCR_PL_1     | DMA_CCR_PL_0;		// Priority
	template <uint32_t ID>
	struct Nvic;
};

template <>
struct DmaBase::Nvic<1>
{
	static constexpr IRQn_Type DmaIrqs[] {
		DMA1_Channel1_IRQn,
		DMA1_Channel2_IRQn,
		DMA1_Channel3_IRQn,
		DMA1_Channel4_IRQn,
		DMA1_Channel5_IRQn,
		DMA1_Channel6_IRQn,
	};
};

template <>
struct DmaBase::Nvic<2>
{
	static constexpr IRQn_Type DmaIrqs[] {
		DMA2_Channel1_IRQn,
		DMA2_Channel2_IRQn,
		DMA2_Channel3_IRQn,
		DMA2_Channel4_IRQn,
		DMA2_Channel5_IRQn,
		DMA2_Channel6_IRQn,
	};
};

}	// namespace platform

}	// namespace modm

#endif	// MODM_STM32_DMA_BASE_HPP