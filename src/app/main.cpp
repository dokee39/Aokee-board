#include "bsp/board.hpp"
#include "app/imu.hpp"
#include "app/led.hpp"

int main()
{
    Board::initialize();
    while (true)
    {
        Task<Led>::poll();
        Task<Imu>::poll();
    }
}

