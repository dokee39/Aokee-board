#pragma once

#include "bsp/board.hpp"
#include "modm/processing/timer/periodic_timer.hpp"

using namespace Board;
using namespace std::chrono_literals;

class Led {
protected:
    Ws2812 ws2812;
    modm::color::Hsv color {0, 166, 50};
    modm::PeriodicTimer timer {3ms};
};

