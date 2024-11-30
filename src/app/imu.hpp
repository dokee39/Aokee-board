#pragma once

#include <numbers>
#include "modm/architecture/driver/atomic/flag.hpp"
#include "bsp/board.hpp"

using namespace Board;

class Imu {
protected:
    static constexpr float ACC_UNIT {1e-3f};
    static constexpr float GYRO_UNIT {std::numbers::pi_v<float> / 180.0f};
    static constexpr float DT_DEFAULT {0.0006f};
    static constexpr float KP {0.5f};
    static constexpr float KI {0.2f};
    static constexpr float EI_MAX {0.02f};

    Bmi088 bmi088;
    Qmc5883::Data qmc5883_data;
    Qmc5883 qmc5883 {qmc5883_data};

    modm::atomic::Flag acc_ready_flag {false};
    modm::atomic::Flag gyro_ready_flag {false};
    modm::atomic::Flag mag_ready_flag {true}; // Initialized to true, otherwise the first read will not be possible.

    modm::Vector3f angle {0.0f};
    modm::Vector4f quat {1.0f, 0.0f, 0.0f, 0.0f};
    modm::Vector3f acc {0.0f};
    modm::Vector3f gyro {0.0f};
    modm::Vector3f mag {0.0f};
    float dt {0.0f};

    bool init();
    bool bmi088DataReady();
    bool qmc5883DataReady();
    void ahrsUpdate();
    void angleUpdate();
};

