/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "tusb.h"

/* A combination of interfaces must have a unique product id, since PC will save
 * device driver after the first plug. Same VID/PID with different interface e.g
 * MSC (first), then CDC (later) will possibly cause system error on PC.
 *
 * Auto ProductID layout's Bitmap:
 *   [MSB]       MIDI | HID | MSC | CDC          [LSB]
 */
#define _PID_MAP(itf, n) ((CFG_TUD_##itf) << (n))
#define USB_PID                                                      \
	(0x4000 | _PID_MAP(CDC, 0) | _PID_MAP(MSC, 2) | _PID_MAP(HID, 3) | \
	_PID_MAP(MIDI, 4) | _PID_MAP(AUDIO, 5) | _PID_MAP(VENDOR, 6))

//--------------------------------------------------------------------+
// Device Descriptors
//--------------------------------------------------------------------+
const tusb_desc_device_t desc_device =
{
	.bLength            = sizeof(tusb_desc_device_t),
	.bDescriptorType    = TUSB_DESC_DEVICE,
	.bcdUSB             = 0x0200,

	// Use Interface Association Descriptor (IAD) for CDC
	// As required by USB Specs IAD's subclass must be common class (2) and protocol must be IAD (1)
	.bDeviceClass       = TUSB_CLASS_MISC,
	.bDeviceSubClass    = MISC_SUBCLASS_COMMON,
	.bDeviceProtocol    = MISC_PROTOCOL_IAD,
	.bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

	.idVendor           = 0xCafe,
	.idProduct          = USB_PID,
	.bcdDevice          = 0x0100,

	.iManufacturer      = 0x01,
	.iProduct           = 0x02,
	.iSerialNumber      = 0x03,

	.bNumConfigurations = 0x01
};

// Invoked when received GET DEVICE DESCRIPTOR
// Application return pointer to descriptor
modm_weak const uint8_t*
tud_descriptor_device_cb(void)
{
	return (uint8_t const *) &desc_device;
}

//--------------------------------------------------------------------+
// Configuration Descriptor
//--------------------------------------------------------------------+
enum
{
	ITF_NUM_CDC0 = 0,
	ITF_NUM_CDC0_DATA,
	ITF_NUM_TOTAL
};

#define CONFIG_TOTAL_LEN (TUD_CONFIG_DESC_LEN + \
	CFG_TUD_CDC         * TUD_CDC_DESC_LEN + \
	CFG_TUD_MSC         * TUD_MSC_DESC_LEN + \
	CFG_TUD_HID         * TUD_HID_DESC_LEN + \
	CFG_TUD_MIDI        * TUD_MIDI_DESC_LEN + \
	CFG_TUD_DFU_RUNTIME * TUD_DFU_RT_DESC_LEN + \
	CFG_TUD_VENDOR      * TUD_VENDOR_DESC_LEN)

#define EPNUM_CDC0_NOTIF 0x81
#define EPNUM_CDC0_OUT 0x2
#define EPNUM_CDC0_IN 0x82
const uint8_t desc_fs_configuration[] =
{
	// Config number, interface count, string index, total length, attribute, power in mA
	TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, TUSB_DESC_CONFIG_ATT_REMOTE_WAKEUP, 100),

	// 1st CDC: Interface number, string index, EP notification address and size, EP data address (out, in) and size.
	TUD_CDC_DESCRIPTOR(ITF_NUM_CDC0, 4, EPNUM_CDC0_NOTIF, 8, EPNUM_CDC0_OUT, EPNUM_CDC0_IN, 64),
};


// Invoked when received GET CONFIGURATION DESCRIPTOR
// Application return pointer to descriptor
// Descriptor contents must exist long enough for transfer to complete
modm_weak const uint8_t*
tud_descriptor_configuration_cb(uint8_t index)
{
	(void)index;  // for multiple configurations
	return desc_fs_configuration;
}

//
//--------------------------------------------------------------------+
// String Descriptors
//--------------------------------------------------------------------+

// array of pointer to string descriptors
modm_weak const char*
tud_string_desc_arr[] =
{
	NULL,				// 0: Language
	"dokee",			// 1: Manufacturer
	"Aokee-board",	// 2: Product
	NULL,				// 3: Serials, should use chip ID
	"Aokee-board CDC",		// 4: CDC0 Interface
};

static uint16_t _desc_str[33];

// Invoked when received GET STRING DESCRIPTOR request
// Application return pointer to descriptor, whose contents must exist long
// enough for transfer to complete
modm_weak const uint16_t*
tud_descriptor_string_cb(uint8_t index, uint16_t langid)
{
	(void)langid;
	uint8_t chr_count = 1;

	if (index == 0)
	{	// supported language is English (0x0409)
		_desc_str[1] = 0x09; _desc_str[2] = 0x04;
	}
	else if (index == 3)
	{
		extern uint8_t tusb_get_device_serial(uint16_t* serial_str);
		chr_count = tusb_get_device_serial(_desc_str + 1);
	}
	else
	{
		if (!(index < sizeof(tud_string_desc_arr) / sizeof(tud_string_desc_arr[0])))
			return NULL;

		const char* str = tud_string_desc_arr[index];

		// Cap at max char
		chr_count = strlen(str);
		if (chr_count > 31) chr_count = 31;

		// Convert ASCII string into UTF-16
		for (uint8_t i = 0; i < chr_count; i++)
			_desc_str[1 + i] = str[i];
	}

	// first byte is length (including header), second byte is string type
	_desc_str[0] = (TUSB_DESC_STRING << 8) | (2 * chr_count + 2);

	return _desc_str;
}
