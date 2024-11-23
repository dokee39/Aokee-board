#pragma once

#include "bsp/board.hpp"
#include "app/task.hpp"

using namespace Board;

class Imu {
protected:
    Bmi088 bmi088;

    std::atomic_bool is_acc_ready {false};
    std::atomic_bool is_gyro_ready {false};
    bool bmi088_init_ok {true};

    modm::Vector4f quat {0.0f};
    modm::Vector3f acc {0.0f};
    modm::Vector3f gyro {0.0f};
    float dt {0.0f};

    void ahrsUpdate();
};

