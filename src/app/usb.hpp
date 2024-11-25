#pragma once

#include "modm/processing/timer.hpp"

using namespace std::chrono_literals;

class Usb {
protected:
    modm::PrecisePeriodicTimer timer {200us};
};
