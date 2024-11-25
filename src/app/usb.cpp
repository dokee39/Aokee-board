#include "app/task.hpp"
#include "app/usb.hpp"
#include "tusb.h"

template<>
bool Task<Usb>::pollInternal() {
    PT_BEGIN();
    tusb_init();

    PT_YIELD();
    while (true) {
        tud_task();
        PT_WAIT_UNTIL(timer.execute());
    }

    PT_END();
}

