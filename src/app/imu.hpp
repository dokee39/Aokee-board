#pragma once

#include "modm/architecture/driver/atomic/flag.hpp"
#include "bsp/board.hpp"

using namespace Board;

class Imu {
protected:
    Bmi088 bmi088;

    modm::atomic::Flag acc_ready_flag {false};
    modm::atomic::Flag gyro_ready_flag {false};
    bool bmi088_init_ok {true};

    modm::Vector4f quat {0.0f};
    modm::Vector3f acc {0.0f};
    modm::Vector3f gyro {0.0f};
    float dt {0.0f};

    void ahrsUpdate();
};

