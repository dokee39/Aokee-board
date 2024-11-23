#pragma once

#include "bsp/board.hpp"
#include "app/task.hpp"

using namespace Board;

class Led {
protected:
    Ws2812 ws2812;
    modm::PreciseTimeout timeout;
};

