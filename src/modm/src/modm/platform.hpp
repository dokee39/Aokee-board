/*
 * Copyright (c) 2016, Sascha Schade
 * Copyright (c) 2017, Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#include <modm/architecture.hpp>

#include "platform/clock/rcc.hpp"
#include "platform/clock/systick_timer.hpp"
#include "platform/core/delay_ns.hpp"
#include "platform/core/hardware_init.hpp"
#include "platform/core/vectors.hpp"
#include "platform/dma/dma.hpp"
#include "platform/dma/dma_base.hpp"
#include "platform/dma/dma_hal.hpp"
#include "platform/exti/exti.hpp"
#include "platform/gpio/base.hpp"
#include "platform/gpio/connector.hpp"
#include "platform/gpio/data.hpp"
#include "platform/gpio/inverted.hpp"
#include "platform/gpio/pins.hpp"
#include "platform/gpio/port.hpp"
#include "platform/gpio/port_shim.hpp"
#include "platform/gpio/set.hpp"
#include "platform/gpio/software_port.hpp"
#include "platform/gpio/static.hpp"
#include "platform/gpio/unused.hpp"
#include "platform/i2c/i2c_master_1.hpp"
#include "platform/i2c/i2c_timing_calculator.hpp"
#include "platform/spi/spi_base.hpp"
#include "platform/spi/spi_hal_1.hpp"
#include "platform/spi/spi_hal_3.hpp"
#include "platform/spi/spi_master_1.hpp"
#include "platform/spi/spi_master_1_dma.hpp"
#include "platform/spi/spi_master_3.hpp"
#include "platform/spi/spi_master_3_dma.hpp"
#include "platform/uart/uart.hpp"
#include "platform/uart/uart_base.hpp"
#include "platform/uart/uart_buffer.hpp"
#include "platform/uart/uart_hal_1.hpp"
#include "platform/uart/uart_hal_2.hpp"
#include "platform/usb/uart.hpp"
#include "platform/usb/usb.hpp"
