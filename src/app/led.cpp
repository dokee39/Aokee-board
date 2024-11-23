#include "led.hpp"

using namespace std::chrono_literals;

template <>
bool Task<Led>::pollInternal() {
    PT_BEGIN();

    ws2812.initialize<SystemClock>();

    PT_YIELD();
    while (true) {
        ws2812.setColor(0, modm::color::Rgb(255, 0, 0));
        ws2812.write();

        timeout.restart(250ms);
        PT_WAIT_UNTIL(timeout.isExpired());
        
        ws2812.setColor(0, modm::color::Rgb(0, 255, 0));
        ws2812.write();

        timeout.restart(250ms);
        PT_WAIT_UNTIL(timeout.isExpired());
        
        ws2812.setColor(0, modm::color::Rgb(0, 0, 255));
        ws2812.write();

        timeout.restart(250ms);
        PT_WAIT_UNTIL(timeout.isExpired());
    }

    PT_END();
}

