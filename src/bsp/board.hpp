#pragma once

#include "modm/platform.hpp"
#include "modm/driver/inertial/bmi088.hpp"
#include "modm/driver/pwm/ws2812b.hpp"
#include "bsp/spi_master_1_dma_block.hpp"

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

using Bmi088Spi = SpiMaster1_DmaBlock<Dma1::Channel1, Dma1::Channel2>;
/*using Bmi088Spi = SpiMaster1;*/
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

using Usbd = UsbFs;
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

    GpioStatic<Rs485UartTx::Data>::setOutput(
        Gpio::OutputType::PushPull, Gpio::OutputSpeed::VeryHigh);
    Rs485Uart::connect<Rs485UartTx, Rs485UartRx>();
    Rs485Uart::initialize<SystemClock, 4_MHz, 0_pct>();

    GpioStatic<Rs485UartDe::Data>::setOutput(
        Gpio::OutputType::PushPull, Gpio::OutputSpeed::VeryHigh);
    GpioStatic<Rs485UartDe::Data>::setAlternateFunction(0x07);
    UsartHal2::disableOperation();
    USART2->CR3 |= USART_CR3_DEM;
    USART2->CR3 = (USART2->CR3 & (~USART_CR3_DEP)) | (/*DE polarity is high*/ true ? 0 : USART_CR3_DEP);
    USART2->CR1 = (USART2->CR1 & ~(USART_CR1_DEDT | USART_CR1_DEAT)) | (/*deassertion time*/ 0u << 16u) | (/*assertion time*/ 0u << 21u);
    UsartHal2::enableOperation();

	GpioSet<Bmi088IntAcc, Bmi088IntGyro>::setInput(
        Gpio::InputType::PullDown);
	GpioSet<Bmi088CsAcc, Bmi088CsGyro>::setOutput(
        Gpio::OutputType::PushPull, Gpio::OutputSpeed::VeryHigh);
	Bmi088Spi::connect<Bmi088SpiSck, Bmi088SpiMiso, Bmi088SpiMosi>();
	Bmi088Spi::initialize<SystemClock, 10.5_MHz, 0_pct>();
}

inline void initializeUsbFs() {
    /*reset*/
    USB->CNTR = (uint16_t)USB_CNTR_FRES;
    USB->CNTR = 0u;
    USB->ISTR = 0u;
    USB->BTABLE = 0u;

    GpioSet<GpioStatic<UsbDp::Data>, GpioStatic<UsbDm::Data>>::setOutput(
        Gpio::OutputType::PushPull, Gpio::OutputSpeed::VeryHigh);
    Usbd::connect<UsbDp, UsbDm>();
    Usbd::initialize<SystemClock>();
}
}
