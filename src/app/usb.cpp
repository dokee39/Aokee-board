#include "util/task.hpp"
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

// Invoked when device is mounted
void tud_mount_cb() {}
// Invoked when device is unmounted
void tud_umount_cb() {}
// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool) {}
// Invoked when usb bus is resumed
void tud_resume_cb() {}

