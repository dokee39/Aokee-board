#include "bsp/board.hpp"
#include "modm/platform.hpp"
#include "app/imu.hpp"

using namespace modm::platform;
using namespace std::chrono_literals;

ImuTask imu_task;

int main()
{
    Board::initialize();
    while (true)
    {
        imu_task.run();
    }
}
