/*
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


#ifndef MODM_STM32_DMA_HAL_HPP
#	error 	"Don't include this file directly, use 'dma.hpp' instead!"
#endif
#include <modm/platform/clock/rcc.hpp>

template <modm::platform::DmaBase::Channel ChannelID, uint32_t CHANNEL_BASE>
void
modm::platform::DmaChannelHal<ChannelID, CHANNEL_BASE>::start()
{
	DMA_Channel_TypeDef *Base = (DMA_Channel_TypeDef *) CHANNEL_BASE;

	Base->CCR |= DMA_CCR_EN;
}

template <modm::platform::DmaBase::Channel ChannelID, uint32_t CHANNEL_BASE>
void
modm::platform::DmaChannelHal<ChannelID, CHANNEL_BASE>::stop()
{
	DMA_Channel_TypeDef *Base = (DMA_Channel_TypeDef *) CHANNEL_BASE;

	Base->CCR &= ~DMA_CCR_EN;
	while (Base->CCR & DMA_CCR_EN); // wait for stream to be stopped
}

template <modm::platform::DmaBase::Channel ChannelID, uint32_t CHANNEL_BASE>
modm::platform::DmaBase::DataTransferDirection
modm::platform::DmaChannelHal<ChannelID, CHANNEL_BASE>::getDataTransferDirection()
{
	DMA_Channel_TypeDef *Base = (DMA_Channel_TypeDef *) CHANNEL_BASE;

	return static_cast<DataTransferDirection>(
		Base->CCR & (DMA_CCR_MEM2MEM | DMA_CCR_DIR));
}