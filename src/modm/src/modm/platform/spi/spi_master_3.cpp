/*
 * Copyright (c) 2009, Martin Rosekeit
 * Copyright (c) 2009-2012, Fabian Greif
 * Copyright (c) 2010, Georgi Grinshpun
 * Copyright (c) 2012-2017, Niklas Hauser
 * Copyright (c) 2013, Kevin Läufer
 * Copyright (c) 2014, Sascha Schade
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#include "spi_master_3.hpp"

modm::ResumableResult<uint8_t>
modm::platform::SpiMaster3::transfer(uint8_t data)
{
	// this is a manually implemented "fast resumable function"
	// there is no context or nesting protection, since we don't need it.
	// there are only two states encoded into 1 bit (LSB of state):
	//   1. waiting to start, and
	//   2. waiting to finish.

	// LSB != Bit0 ?
	if ( !(state & Bit0) )
	{
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

modm::ResumableResult<void>
modm::platform::SpiMaster3::transfer(
		const uint8_t * tx, uint8_t * rx, std::size_t length)
{
	// this is a manually implemented "fast resumable function"
	// there is no context or nesting protection, since we don't need it.
	// there are only two states encoded into 1 bit (Bit1 of state):
	//   1. initialize index, and
	//   2. wait for 1-byte transfer to finish.

	// we need to globally remember which byte we are currently transferring
	static std::size_t index = 0;

	// we are only interested in Bit1
	switch(state & Bit1)
	{
		case 0:
			// we will only visit this state once
			state |= Bit1;

			// initialize index and check range
			index = 0;
			while (index < length)
			{
		default:
		{
				// if tx == 0, we use a dummy byte 0x00
				// else we copy it from the array
				// call the resumable function
				modm::ResumableResult<uint8_t> result = transfer(tx ? tx[index] : 0);

				// if the resumable function is still running, so are we
				if (result.getState() > modm::rf::NestingError)
					return {modm::rf::Running};

				// if rx != 0, we copy the result into the array
				if (rx) rx[index] = result.getResult();
		}
				index++;
			}

			// clear the state
			state &= ~Bit1;
			return {modm::rf::Stop};
	}
}