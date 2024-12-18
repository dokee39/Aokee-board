/*
 * Copyright (c) 2020, 2023, Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#pragma once

#include <modm/platform/device.hpp>

#if __has_include(<tusb_config_local.h>)
#	include <tusb_config_local.h>
#endif

#ifndef CFG_TUD_CDC
#	define CFG_TUD_CDC 1
#endif

#ifndef CFG_TUD_CDC_RX_BUFSIZE
#	define CFG_TUD_CDC_RX_BUFSIZE 64
#endif

#ifndef CFG_TUD_CDC_TX_BUFSIZE
#	define CFG_TUD_CDC_TX_BUFSIZE 64
#endif

#ifndef CFG_TUSB_MCU
#	define CFG_TUSB_MCU OPT_MCU_STM32G4
#endif

#ifndef CFG_TUSB_RHPORT0_MODE
#	define CFG_TUSB_RHPORT0_MODE OPT_MODE_DEVICE
#endif


#include <modm/architecture/interface/assert.h>

// Redirect TinyUSB asserts to use modm_assert
#define MODM_ASSERT_1ARGS(_cond) \
	do { \
		modm_assert(_cond, "tu", __FILE__ ":" MODM_STRINGIFY(__LINE__) " -> \"" #_cond "\""); \
	} while(0)

#define MODM_ASSERT_2ARGS(_cond, _ret) \
	do { \
		if (!modm_assert_continue_fail(_cond, "tu", __FILE__ ":" MODM_STRINGIFY(__LINE__) " -> \"" #_cond "\"")) \
		{ return _ret; } \
	} while(0)

#define TU_ASSERT(...) _GET_3RD_ARG(__VA_ARGS__, MODM_ASSERT_2ARGS, MODM_ASSERT_1ARGS,UNUSED)(__VA_ARGS__)
