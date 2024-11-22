#pragma once

#include "modm/processing/protothread.hpp"
#include "bsp/board.hpp"

using namespace Board;

class LedTask: public modm::pt::Protothread{
public:
    bool run();
private:
    Ws2812 ws2812;
    modm::PreciseTimeout timeout;
};
