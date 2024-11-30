#include "app/imu.hpp"
#include "util/task.hpp"
#include "util/util.hpp"

// debug
struct [[gnu::packed]] PrintData {
    float data[3];
    uint8_t tail[4] = {0x00, 0x00, 0x80, 0x7f};
};

template <>
bool Task<Imu>::pollInternal() {
    PT_BEGIN();

    PT_WAIT_UNTIL(init());

	Exti::connect<Bmi088IntAcc>(Exti::Trigger::RisingEdge, [&](auto){
		acc_ready_flag.set();
	});
	Exti::connect<Bmi088IntGyro>(Exti::Trigger::RisingEdge, [&](auto){
		gyro_ready_flag.set();
	});

    PT_YIELD();
    while (true) {
        PT_WAIT_UNTIL(dataReady());

        {
            static auto t = modm::PreciseClock::now();
            auto t_now = modm::PreciseClock::now();
            dt = t_now > t ? (t_now - t).count() * 1e-6f : DT_DEFAULT;
            t = t_now;
        }

		const std::optional acc_result = bmi088.readAccData();
		acc_ready_flag.reset();
		if (acc_result) {
			acc = acc_result->getFloat() * ACC_UNIT;
		}

		const std::optional gyro_result = bmi088.readGyroData();
		gyro_ready_flag.reset();
		if (gyro_result) {
			gyro = gyro_result->getFloat() * GYRO_UNIT;
		}

		ahrsUpdate();
        angleUpdate();

        { // debug
            static PrintData pd;
            pd.data[0] = angle[0];
            pd.data[1] = angle[1];
            pd.data[2] = angle[2];

            Rs485Uart::writeBlocking((uint8_t *)&pd, sizeof(pd));
        }
        
	}

    PT_END();
}

bool Imu::init() {
    if (not bmi088.initialize(true)) {
        return false;
    }

    bool ret {true};

    ret &= bmi088.setAccRate(Bmi088::AccRate::Rate1600Hz_Bw145Hz);
    ret &= bmi088.setAccRange(Bmi088::AccRange::Range3g);
    ret &= bmi088.setAccInt1GpioConfig(Bmi088::AccGpioConfig::ActiveHigh |
                                       Bmi088::AccGpioConfig::EnableOutput);
    ret &= bmi088.setAccGpioMap(Bmi088::AccGpioMap::Int1DataReady);

    ret &= bmi088.setGyroRate(Bmi088::GyroRate::Rate2000Hz_Bw230Hz);
    ret &= bmi088.setGyroRange(Bmi088::GyroRange::Range2000dps);
    ret &= bmi088.setGyroGpioConfig(Bmi088::GyroGpioConfig::Int3ActiveHigh);
    ret &= bmi088.setGyroGpioMap(Bmi088::GyroGpioMap::Int3DataReady);

    return ret;
}

inline bool Imu::dataReady() {
    return acc_ready_flag.test() and gyro_ready_flag.test();
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
        gyro[0],        0,  gyro[2], -gyro[1],
        gyro[1], -gyro[2],        0,  gyro[0],
        gyro[2],  gyro[1], -gyro[0],        0,
    };
    quat += 0.5f * dt * m * quat.asMatrix();
    quat.normalize();
}

void Imu::angleUpdate()
{
    angle[0] = std::atan2f(2.0f * (quat[0] * quat[1] + quat[2] * quat[3]),
                           2.0f * (quat[0] * quat[0] + quat[3] * quat[3]) - 1.0f);
    angle[1] = std::asinf(-2.0f * (quat[1] * quat[3] - quat[0] * quat[2]));
    angle[2] = std::atan2f(2.0f * (quat[0] * quat[3] + quat[1] * quat[2]),
                           2.0f * (quat[0] * quat[0] + quat[1] * quat[1]) - 1.0f);
}

