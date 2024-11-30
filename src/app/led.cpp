#include "led.hpp"
#include "util/task.hpp"

template <>
bool Task<Led>::pollInternal() {
    PT_BEGIN();

    ws2812.initialize<SystemClock>();
    Ws2812Spi::setDataMode(Ws2812Spi::DataMode::Mode3);

    PT_YIELD();
    while (true) {
        {
            color.hue++;
            ws2812.setColor(0, color);
            ws2812.write();
        }
        PT_WAIT_UNTIL(timer.execute());
    }

    PT_END();
}

