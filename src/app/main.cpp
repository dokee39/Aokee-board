#include "bsp/board.hpp"
#include "app/task.hpp"
#include "app/imu.hpp"
#include "app/led.hpp"
#include "app/usb.hpp"

#include "modm/platform.hpp"

int main()
{
    Board::initialize();
    Board::initializeUsbFs();
    while (true)
    {
        Task<Led>::poll();
        Task<Imu>::poll();
        Task<Usb>::poll();
    }
}

