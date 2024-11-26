#pragma once

#include "modm/platform.hpp"
#include "modm/processing/timer.hpp"
#include "modm/io.hpp"

using namespace modm::platform;
using namespace std::chrono_literals;

class Usb {
protected:
    modm::PrecisePeriodicTimer timer {20ms};
    modm::IODeviceWrapper<UsbUart0, modm::IOBuffer::BlockIfFull> usb_uart0_io;
    modm::IOStream usb_uart0_stream {usb_uart0_io};
};
