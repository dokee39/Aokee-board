#pragma once

#include "modm/platform.hpp"
#include <modm/driver/inertial/bmi088.hpp>
#include <modm/driver/pwm/ws2812b.hpp>

using namespace modm::platform;
using namespace modm::literals;

namespace Board {
using UserKey = GpioA0;

using DbusUart = BufferedUart<UsartHal1>;
using DbusUartRx = GpioA10::Rx;

using Rs485Uart = BufferedUart<UsartHal2>;
using Rs485UartDe = GpioA1::De;
using Rs485UartTx = GpioA2::Tx;
using Rs485UartRx = GpioA3::Rx;

using Bmi088Spi = SpiMaster1_Dma<Dma1::Channel1, Dma1::Channel2>;
using Bmi088SpiSck = GpioA5::Sck;
using Bmi088SpiMiso = GpioA6::Miso;
using Bmi088SpiMosi = GpioA7::Mosi;
using Bmi088IntGyro = GpioA4;
using Bmi088IntAcc = GpioB0;
using Bmi088CsGyro = GpioB4;
using Bmi088CsAcc = GpioA8;
using Bmi088Transport = modm::Bmi088SpiTransport<Bmi088Spi, Bmi088CsAcc, Bmi088CsGyro>;
using Bmi088 = modm::Bmi088<Bmi088Transport>;

using Ws2812Spi = SpiMaster3;
using Ws2812SpiMosi = GpioB5::Mosi;
using Ws2812 = modm::Ws2812b<Ws2812Spi, Ws2812SpiMosi, 1>;

using Qmc5883lI2c = I2cMaster1;
using Qmc5883lI2cScl = GpioA15::Scl;
using Qmc5883lI2cSda = GpioB7::Sda;
using Qmc5883lDrdy = GpioB6;

using Usb = UsbFs;
using UsbDp = GpioA12::Dp;
using UsbDm = GpioA11::Dm;

struct SystemClock {
	static constexpr uint32_t Frequency = 168_MHz;
	static constexpr uint32_t Ahb = Frequency;
	static constexpr uint32_t Apb1 = Frequency;
	static constexpr uint32_t Apb2 = Frequency;

	static constexpr uint32_t Spi1 = Apb2;
	static constexpr uint32_t Spi3 = Apb1;

	static constexpr uint32_t I2c1 = Apb1;

	static constexpr uint32_t Usart1 = Apb2;
	static constexpr uint32_t Usart2 = Apb1;

	static constexpr uint32_t Usb = 48_MHz;

	static inline bool enable() {
        Rcc::enableExternalCrystal(); // 12 MHz
        Rcc::PllFactors pllF = {
            1,  // 12MHz / M=1  -> 12MHz
            28, // 12MHz * N=28 -> 336MHz
            2,  // 336MHz / P=2 -> 168MHz = F_cpu
            2,  // not used
        };
        Rcc::enablePll(Rcc::PllSource::ExternalCrystal, pllF);
		Rcc::setFlashLatency<Frequency>();
		// switch system clock to PLL output
		Rcc::enableSystemClock(Rcc::SystemClockSource::Pll);
		Rcc::setAhbPrescaler(Rcc::AhbPrescaler::Div1);
		Rcc::setApb1Prescaler(Rcc::Apb1Prescaler::Div1);
		Rcc::setApb2Prescaler(Rcc::Apb2Prescaler::Div1);
	    Rcc::setClock48Source(Rcc::Clock48Source::Hsi48);
        RCC->CRRCR |= RCC_CRRCR_HSI48ON; // TODO enable HSI48
        while((RCC->CRRCR & RCC_CRRCR_HSI48RDY) == 0U) {}
		// update frequencies for busy-wait delay functions
		Rcc::updateCoreFrequency<Frequency>();

		return true;
	}
};

inline void initialize() {
	SystemClock::enable();
	SysTickTimer::initialize<SystemClock>();

    Dma1::enable();

    /*DbusUart::connect<DbusUartRx>();*/
    /*Rs485Uart::connect<Rs485UartTx, Rs485UartRx>();*/

	Bmi088IntGyro::setInput(Bmi088IntGyro::InputType::PullDown);
	Bmi088IntAcc::setInput(Bmi088IntAcc::InputType::PullDown);
	Bmi088Spi::connect<Bmi088SpiSck, Bmi088SpiMiso, Bmi088SpiMosi>();
	Bmi088Spi::initialize<SystemClock, 5.25_MHz, 0_pct>();
    Bmi088Spi::setDataMode(Bmi088Spi::DataMode::Mode1);

    Usb::connect<UsbDp, UsbDm>();
    Usb::initialize<SystemClock>();
}
}
