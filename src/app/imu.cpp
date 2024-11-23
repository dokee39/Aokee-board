#include "app/imu.hpp"
#include "util.hpp"

#define KP 0.5f
#define KI 0.1f
#define EI_MAX 0.02f

template <>
bool Task<Imu>::pollInternal() {
    PT_BEGIN();

    PT_WAIT_UNTIL(bmi088.initialize(true));

    bmi088_init_ok &= bmi088.setAccRate(Bmi088::AccRate::Rate12Hz_Bw5Hz);
	bmi088_init_ok &= bmi088.setAccRange(Bmi088::AccRange::Range3g);
	bmi088_init_ok &= bmi088.setAccInt1GpioConfig(Bmi088::AccGpioConfig::ActiveHigh | Bmi088::AccGpioConfig::EnableOutput);
	bmi088_init_ok &= bmi088.setAccGpioMap(Bmi088::AccGpioMap::Int1DataReady);
	bmi088_init_ok &= bmi088.setGyroRate(Bmi088::GyroRate::Rate100Hz_Bw12Hz);
	bmi088_init_ok &= bmi088.setGyroRange(Bmi088::GyroRange::Range250dps);
	bmi088_init_ok &= bmi088.setGyroGpioConfig(Bmi088::GyroGpioConfig::Int3ActiveHigh);
	bmi088_init_ok &= bmi088.setGyroGpioMap(Bmi088::GyroGpioMap::Int3DataReady);

    // TODO bmi088_init_ok

	Exti::connect<Bmi088IntAcc>(Exti::Trigger::RisingEdge, [&](auto){
		is_acc_ready = true;
	});
	Exti::connect<Bmi088IntGyro>(Exti::Trigger::RisingEdge, [&](auto){
		is_gyro_ready = true;
	});

    PT_YIELD();
    while (true) {
        PT_WAIT_UNTIL(is_acc_ready and is_gyro_ready);

        {
            static auto t = modm::PreciseClock::now();
            auto t_now = modm::PreciseClock::now();
            if (t_now > t) {
                dt = std::chrono::duration_cast<std::chrono::microseconds>(t_now - t).count() / 1000000.0f;
            }
            t = t_now;
        }

		const std::optional acc_result = bmi088.readAccData();
		is_acc_ready = false;
		if (acc_result) {
			acc = acc_result->getFloat();
		}

		const std::optional gyro_result = bmi088.readGyroData();
		is_gyro_ready = false;
		if (gyro_result) {
			gyro = gyro_result->getFloat();
		}

        ahrsUpdate();
	}

    PT_END();
}

void Imu::ahrsUpdate() {
    acc.normalize();

    if(acc[0] != 0.0f or acc[1] != 0.0f or acc[2] != 0.0f) {
        modm::Vector3f v {
            2.0f * (quat[1] * quat[1] - quat[0] * quat[2]),
            2.0f * (quat[0] * quat[1] + quat[2] * quat[3]),
            2.0f * (quat[0] * quat[0] + quat[3] * quat[3]) - 1,
        };

        modm::Vector3f e = acc ^ v;

        static modm::Vector3f ei {0.0f};
        ei += KI * dt * e;
        limit(EI_MAX)(ei);
        gyro += KP * e + ei;

    }

    modm::Matrix<float, 4, 4> m {
              0, -gyro[0], -gyro[1], -gyro[2],
        gyro[0],        0,  gyro[1], -gyro[2],
        gyro[0], -gyro[1],        0,  gyro[2],
        gyro[0],  gyro[1], -gyro[2],        0,
    };
    quat += 0.5f * dt * m * quat.asMatrix();
    quat.normalize();
}


