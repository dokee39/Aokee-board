/*
 * Copyright (c) 2021, Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#pragma once

#include "base.hpp"

/// @cond
namespace modm::platform::detail
{

template<class Signal, Peripheral p> struct SignalConnection;
template<class Data, Peripheral p> static constexpr int8_t AdcChannel = -1;
template<class Data, Peripheral p> static constexpr int8_t DacChannel = -1;

struct DataUnused {};

struct DataA0 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 0;
	struct BitBang { using Data = DataA0; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Bkin { using Data = DataA0; static constexpr Gpio::Signal Signal = Gpio::Signal::Bkin; };
	struct Ch1 { using Data = DataA0; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1; };
	struct Cts { using Data = DataA0; static constexpr Gpio::Signal Signal = Gpio::Signal::Cts; };
	struct Etr { using Data = DataA0; static constexpr Gpio::Signal Signal = Gpio::Signal::Etr; };
	struct In1 { using Data = DataA0; static constexpr Gpio::Signal Signal = Gpio::Signal::In1; };
	struct Inm { using Data = DataA0; static constexpr Gpio::Signal Signal = Gpio::Signal::Inm; };
	struct Inp { using Data = DataA0; static constexpr Gpio::Signal Signal = Gpio::Signal::Inp; };
	struct Nss { using Data = DataA0; static constexpr Gpio::Signal Signal = Gpio::Signal::Nss; };
	struct Out { using Data = DataA0; static constexpr Gpio::Signal Signal = Gpio::Signal::Out; };
	struct Tamp2 { using Data = DataA0; static constexpr Gpio::Signal Signal = Gpio::Signal::Tamp2; };
	struct Wkup1 { using Data = DataA0; static constexpr Gpio::Signal Signal = Gpio::Signal::Wkup1; };
};
template<Peripheral p> struct SignalConnection<DataA0::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA0::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA0::Bkin, p> {
	static_assert((p == Peripheral::Tim8),"GpioA0::Bkin only connects to Tim8!"); };
template<Peripheral p> struct SignalConnection<DataA0::Ch1, p> {
	static_assert((p == Peripheral::Tim2),"GpioA0::Ch1 only connects to Tim2!"); };
template<Peripheral p> struct SignalConnection<DataA0::Cts, p> {
	static_assert((p == Peripheral::Usart2),"GpioA0::Cts only connects to Usart2!"); };
template<Peripheral p> struct SignalConnection<DataA0::Etr, p> {
	static_assert((p == Peripheral::Tim8) or (p == Peripheral::Tim2),
		"GpioA0::Etr only connects to Tim8 or Tim2!"); };
template<Peripheral p> struct SignalConnection<DataA0::In1, p> {
	static_assert((p == Peripheral::Adc1) or (p == Peripheral::Adc2),
		"GpioA0::In1 only connects to Adc1 or Adc2!"); };
template<Peripheral p> struct SignalConnection<DataA0::Inm, p> {
	static_assert((p == Peripheral::Comp1),"GpioA0::Inm only connects to Comp1!"); };
template<Peripheral p> struct SignalConnection<DataA0::Inp, p> {
	static_assert((p == Peripheral::Comp3),"GpioA0::Inp only connects to Comp3!"); };
template<Peripheral p> struct SignalConnection<DataA0::Nss, p> {
	static_assert((p == Peripheral::Usart2),"GpioA0::Nss only connects to Usart2!"); };
template<Peripheral p> struct SignalConnection<DataA0::Out, p> {
	static_assert((p == Peripheral::Comp1),"GpioA0::Out only connects to Comp1!"); };
template<Peripheral p> struct SignalConnection<DataA0::Tamp2, p> {
	static_assert((p == Peripheral::Rtc),"GpioA0::Tamp2 only connects to Rtc!"); };
template<Peripheral p> struct SignalConnection<DataA0::Wkup1, p> {
	static_assert((p == Peripheral::Sys),"GpioA0::Wkup1 only connects to Sys!"); };
template<> struct SignalConnection<DataA0::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA0::Bkin, Peripheral::Tim8> { static constexpr int8_t af = 9; };
template<> struct SignalConnection<DataA0::Ch1, Peripheral::Tim2> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataA0::Cts, Peripheral::Usart2> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataA0::Etr, Peripheral::Tim8> { static constexpr int8_t af = 10; };
template<> struct SignalConnection<DataA0::Etr, Peripheral::Tim2> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataA0::In1, Peripheral::Adc1> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA0::In1, Peripheral::Adc2> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA0::Inm, Peripheral::Comp1> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA0::Inp, Peripheral::Comp3> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA0::Nss, Peripheral::Usart2> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataA0::Out, Peripheral::Comp1> { static constexpr int8_t af = 8; };
template<> struct SignalConnection<DataA0::Tamp2, Peripheral::Rtc> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA0::Wkup1, Peripheral::Sys> { static constexpr int8_t af = -1; };
template<> constexpr int8_t AdcChannel<DataA0, Peripheral::Adc1> = 1;
template<> constexpr int8_t AdcChannel<DataA0, Peripheral::Adc2> = 1;

struct DataA1 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 1;
	struct BitBang { using Data = DataA1; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ch1n { using Data = DataA1; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1n; };
	struct Ch2 { using Data = DataA1; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2; };
	struct De { using Data = DataA1; static constexpr Gpio::Signal Signal = Gpio::Signal::De; };
	struct In2 { using Data = DataA1; static constexpr Gpio::Signal Signal = Gpio::Signal::In2; };
	struct Inp { using Data = DataA1; static constexpr Gpio::Signal Signal = Gpio::Signal::Inp; };
	struct Refin { using Data = DataA1; static constexpr Gpio::Signal Signal = Gpio::Signal::Refin; };
	struct Rts { using Data = DataA1; static constexpr Gpio::Signal Signal = Gpio::Signal::Rts; };
	struct Vinp { using Data = DataA1; static constexpr Gpio::Signal Signal = Gpio::Signal::Vinp; };
	struct Vinpsec { using Data = DataA1; static constexpr Gpio::Signal Signal = Gpio::Signal::Vinpsec; };
};
template<Peripheral p> struct SignalConnection<DataA1::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA1::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA1::Ch1n, p> {
	static_assert((p == Peripheral::Tim15),"GpioA1::Ch1n only connects to Tim15!"); };
template<Peripheral p> struct SignalConnection<DataA1::Ch2, p> {
	static_assert((p == Peripheral::Tim2),"GpioA1::Ch2 only connects to Tim2!"); };
template<Peripheral p> struct SignalConnection<DataA1::De, p> {
	static_assert((p == Peripheral::Usart2),"GpioA1::De only connects to Usart2!"); };
template<Peripheral p> struct SignalConnection<DataA1::In2, p> {
	static_assert((p == Peripheral::Adc1) or (p == Peripheral::Adc2),
		"GpioA1::In2 only connects to Adc1 or Adc2!"); };
template<Peripheral p> struct SignalConnection<DataA1::Inp, p> {
	static_assert((p == Peripheral::Comp1),"GpioA1::Inp only connects to Comp1!"); };
template<Peripheral p> struct SignalConnection<DataA1::Refin, p> {
	static_assert((p == Peripheral::Rtc),"GpioA1::Refin only connects to Rtc!"); };
template<Peripheral p> struct SignalConnection<DataA1::Rts, p> {
	static_assert((p == Peripheral::Usart2),"GpioA1::Rts only connects to Usart2!"); };
template<Peripheral p> struct SignalConnection<DataA1::Vinp, p> {
	static_assert((p == Peripheral::Opamp1) or (p == Peripheral::Opamp3),
		"GpioA1::Vinp only connects to Opamp1 or Opamp3!"); };
template<Peripheral p> struct SignalConnection<DataA1::Vinpsec, p> {
	static_assert((p == Peripheral::Opamp1) or (p == Peripheral::Opamp3),
		"GpioA1::Vinpsec only connects to Opamp1 or Opamp3!"); };
template<> struct SignalConnection<DataA1::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA1::Ch1n, Peripheral::Tim15> { static constexpr int8_t af = 9; };
template<> struct SignalConnection<DataA1::Ch2, Peripheral::Tim2> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataA1::De, Peripheral::Usart2> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataA1::In2, Peripheral::Adc1> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA1::In2, Peripheral::Adc2> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA1::Inp, Peripheral::Comp1> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA1::Refin, Peripheral::Rtc> { static constexpr int8_t af = 0; };
template<> struct SignalConnection<DataA1::Rts, Peripheral::Usart2> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataA1::Vinp, Peripheral::Opamp1> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA1::Vinp, Peripheral::Opamp3> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA1::Vinpsec, Peripheral::Opamp1> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA1::Vinpsec, Peripheral::Opamp3> { static constexpr int8_t af = -1; };
template<> constexpr int8_t AdcChannel<DataA1, Peripheral::Adc1> = 2;
template<> constexpr int8_t AdcChannel<DataA1, Peripheral::Adc2> = 2;

struct DataA2 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 2;
	struct BitBang { using Data = DataA2; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ch1 { using Data = DataA2; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1; };
	struct Ch3 { using Data = DataA2; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch3; };
	struct Frstx1 { using Data = DataA2; static constexpr Gpio::Signal Signal = Gpio::Signal::Frstx1; };
	struct Frstx2 { using Data = DataA2; static constexpr Gpio::Signal Signal = Gpio::Signal::Frstx2; };
	struct In3 { using Data = DataA2; static constexpr Gpio::Signal Signal = Gpio::Signal::In3; };
	struct Inm { using Data = DataA2; static constexpr Gpio::Signal Signal = Gpio::Signal::Inm; };
	struct Lsco { using Data = DataA2; static constexpr Gpio::Signal Signal = Gpio::Signal::Lsco; };
	struct Out { using Data = DataA2; static constexpr Gpio::Signal Signal = Gpio::Signal::Out; };
	struct Tx { using Data = DataA2; static constexpr Gpio::Signal Signal = Gpio::Signal::Tx; };
	struct Vout { using Data = DataA2; static constexpr Gpio::Signal Signal = Gpio::Signal::Vout; };
	struct Wkup4 { using Data = DataA2; static constexpr Gpio::Signal Signal = Gpio::Signal::Wkup4; };
};
template<Peripheral p> struct SignalConnection<DataA2::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA2::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA2::Ch1, p> {
	static_assert((p == Peripheral::Tim15),"GpioA2::Ch1 only connects to Tim15!"); };
template<Peripheral p> struct SignalConnection<DataA2::Ch3, p> {
	static_assert((p == Peripheral::Tim2),"GpioA2::Ch3 only connects to Tim2!"); };
template<Peripheral p> struct SignalConnection<DataA2::Frstx1, p> {
	static_assert((p == Peripheral::Ucpd1),"GpioA2::Frstx1 only connects to Ucpd1!"); };
template<Peripheral p> struct SignalConnection<DataA2::Frstx2, p> {
	static_assert((p == Peripheral::Ucpd1),"GpioA2::Frstx2 only connects to Ucpd1!"); };
template<Peripheral p> struct SignalConnection<DataA2::In3, p> {
	static_assert((p == Peripheral::Adc1),"GpioA2::In3 only connects to Adc1!"); };
template<Peripheral p> struct SignalConnection<DataA2::Inm, p> {
	static_assert((p == Peripheral::Comp2),"GpioA2::Inm only connects to Comp2!"); };
template<Peripheral p> struct SignalConnection<DataA2::Lsco, p> {
	static_assert((p == Peripheral::Rcc),"GpioA2::Lsco only connects to Rcc!"); };
template<Peripheral p> struct SignalConnection<DataA2::Out, p> {
	static_assert((p == Peripheral::Comp2),"GpioA2::Out only connects to Comp2!"); };
template<Peripheral p> struct SignalConnection<DataA2::Tx, p> {
	static_assert((p == Peripheral::Usart2) or (p == Peripheral::Lpuart1),
		"GpioA2::Tx only connects to Usart2 or Lpuart1!"); };
template<Peripheral p> struct SignalConnection<DataA2::Vout, p> {
	static_assert((p == Peripheral::Opamp1),"GpioA2::Vout only connects to Opamp1!"); };
template<Peripheral p> struct SignalConnection<DataA2::Wkup4, p> {
	static_assert((p == Peripheral::Sys),"GpioA2::Wkup4 only connects to Sys!"); };
template<> struct SignalConnection<DataA2::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA2::Ch1, Peripheral::Tim15> { static constexpr int8_t af = 9; };
template<> struct SignalConnection<DataA2::Ch3, Peripheral::Tim2> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataA2::Frstx1, Peripheral::Ucpd1> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataA2::Frstx2, Peripheral::Ucpd1> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataA2::In3, Peripheral::Adc1> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA2::Inm, Peripheral::Comp2> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA2::Lsco, Peripheral::Rcc> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA2::Out, Peripheral::Comp2> { static constexpr int8_t af = 8; };
template<> struct SignalConnection<DataA2::Tx, Peripheral::Usart2> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataA2::Tx, Peripheral::Lpuart1> { static constexpr int8_t af = 12; };
template<> struct SignalConnection<DataA2::Vout, Peripheral::Opamp1> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA2::Wkup4, Peripheral::Sys> { static constexpr int8_t af = -1; };
template<> constexpr int8_t AdcChannel<DataA2, Peripheral::Adc1> = 3;

struct DataA3 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 3;
	struct BitBang { using Data = DataA3; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ch2 { using Data = DataA3; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2; };
	struct Ch4 { using Data = DataA3; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch4; };
	struct Ck1 { using Data = DataA3; static constexpr Gpio::Signal Signal = Gpio::Signal::Ck1; };
	struct In4 { using Data = DataA3; static constexpr Gpio::Signal Signal = Gpio::Signal::In4; };
	struct Inp { using Data = DataA3; static constexpr Gpio::Signal Signal = Gpio::Signal::Inp; };
	struct Mclka { using Data = DataA3; static constexpr Gpio::Signal Signal = Gpio::Signal::Mclka; };
	struct Rx { using Data = DataA3; static constexpr Gpio::Signal Signal = Gpio::Signal::Rx; };
	struct Vinm { using Data = DataA3; static constexpr Gpio::Signal Signal = Gpio::Signal::Vinm; };
	struct Vinm0 { using Data = DataA3; static constexpr Gpio::Signal Signal = Gpio::Signal::Vinm0; };
	struct Vinmsec { using Data = DataA3; static constexpr Gpio::Signal Signal = Gpio::Signal::Vinmsec; };
	struct Vinp { using Data = DataA3; static constexpr Gpio::Signal Signal = Gpio::Signal::Vinp; };
	struct Vinpsec { using Data = DataA3; static constexpr Gpio::Signal Signal = Gpio::Signal::Vinpsec; };
};
template<Peripheral p> struct SignalConnection<DataA3::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA3::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA3::Ch2, p> {
	static_assert((p == Peripheral::Tim15),"GpioA3::Ch2 only connects to Tim15!"); };
template<Peripheral p> struct SignalConnection<DataA3::Ch4, p> {
	static_assert((p == Peripheral::Tim2),"GpioA3::Ch4 only connects to Tim2!"); };
template<Peripheral p> struct SignalConnection<DataA3::Ck1, p> {
	static_assert((p == Peripheral::Sai1),"GpioA3::Ck1 only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataA3::In4, p> {
	static_assert((p == Peripheral::Adc1),"GpioA3::In4 only connects to Adc1!"); };
template<Peripheral p> struct SignalConnection<DataA3::Inp, p> {
	static_assert((p == Peripheral::Comp2),"GpioA3::Inp only connects to Comp2!"); };
template<Peripheral p> struct SignalConnection<DataA3::Mclka, p> {
	static_assert((p == Peripheral::Sai1),"GpioA3::Mclka only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataA3::Rx, p> {
	static_assert((p == Peripheral::Usart2) or (p == Peripheral::Lpuart1),
		"GpioA3::Rx only connects to Usart2 or Lpuart1!"); };
template<Peripheral p> struct SignalConnection<DataA3::Vinm, p> {
	static_assert((p == Peripheral::Opamp1),"GpioA3::Vinm only connects to Opamp1!"); };
template<Peripheral p> struct SignalConnection<DataA3::Vinm0, p> {
	static_assert((p == Peripheral::Opamp1),"GpioA3::Vinm0 only connects to Opamp1!"); };
template<Peripheral p> struct SignalConnection<DataA3::Vinmsec, p> {
	static_assert((p == Peripheral::Opamp1),"GpioA3::Vinmsec only connects to Opamp1!"); };
template<Peripheral p> struct SignalConnection<DataA3::Vinp, p> {
	static_assert((p == Peripheral::Opamp1),"GpioA3::Vinp only connects to Opamp1!"); };
template<Peripheral p> struct SignalConnection<DataA3::Vinpsec, p> {
	static_assert((p == Peripheral::Opamp1),"GpioA3::Vinpsec only connects to Opamp1!"); };
template<> struct SignalConnection<DataA3::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA3::Ch2, Peripheral::Tim15> { static constexpr int8_t af = 9; };
template<> struct SignalConnection<DataA3::Ch4, Peripheral::Tim2> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataA3::Ck1, Peripheral::Sai1> { static constexpr int8_t af = 3; };
template<> struct SignalConnection<DataA3::In4, Peripheral::Adc1> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA3::Inp, Peripheral::Comp2> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA3::Mclka, Peripheral::Sai1> { static constexpr int8_t af = 13; };
template<> struct SignalConnection<DataA3::Rx, Peripheral::Usart2> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataA3::Rx, Peripheral::Lpuart1> { static constexpr int8_t af = 12; };
template<> struct SignalConnection<DataA3::Vinm, Peripheral::Opamp1> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA3::Vinm0, Peripheral::Opamp1> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA3::Vinmsec, Peripheral::Opamp1> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA3::Vinp, Peripheral::Opamp1> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA3::Vinpsec, Peripheral::Opamp1> { static constexpr int8_t af = -1; };
template<> constexpr int8_t AdcChannel<DataA3, Peripheral::Adc1> = 4;

struct DataA4 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 4;
	struct BitBang { using Data = DataA4; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ch2 { using Data = DataA4; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2; };
	struct Ck { using Data = DataA4; static constexpr Gpio::Signal Signal = Gpio::Signal::Ck; };
	struct Fsb { using Data = DataA4; static constexpr Gpio::Signal Signal = Gpio::Signal::Fsb; };
	struct In17 { using Data = DataA4; static constexpr Gpio::Signal Signal = Gpio::Signal::In17; };
	struct Inm { using Data = DataA4; static constexpr Gpio::Signal Signal = Gpio::Signal::Inm; };
	struct Nss { using Data = DataA4; static constexpr Gpio::Signal Signal = Gpio::Signal::Nss; };
	struct Out1 { using Data = DataA4; static constexpr Gpio::Signal Signal = Gpio::Signal::Out1; };
	struct Ws { using Data = DataA4; static constexpr Gpio::Signal Signal = Gpio::Signal::Ws; };
};
template<Peripheral p> struct SignalConnection<DataA4::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA4::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA4::Ch2, p> {
	static_assert((p == Peripheral::Tim3),"GpioA4::Ch2 only connects to Tim3!"); };
template<Peripheral p> struct SignalConnection<DataA4::Ck, p> {
	static_assert((p == Peripheral::Usart2),"GpioA4::Ck only connects to Usart2!"); };
template<Peripheral p> struct SignalConnection<DataA4::Fsb, p> {
	static_assert((p == Peripheral::Sai1),"GpioA4::Fsb only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataA4::In17, p> {
	static_assert((p == Peripheral::Adc2),"GpioA4::In17 only connects to Adc2!"); };
template<Peripheral p> struct SignalConnection<DataA4::Inm, p> {
	static_assert((p == Peripheral::Comp1),"GpioA4::Inm only connects to Comp1!"); };
template<Peripheral p> struct SignalConnection<DataA4::Nss, p> {
	static_assert((p == Peripheral::Spi1) or (p == Peripheral::Spi3),
		"GpioA4::Nss only connects to Spi1 or Spi3!"); };
template<Peripheral p> struct SignalConnection<DataA4::Out1, p> {
	static_assert((p == Peripheral::Dac1),"GpioA4::Out1 only connects to Dac1!"); };
template<Peripheral p> struct SignalConnection<DataA4::Ws, p> {
	static_assert((p == Peripheral::I2s3),"GpioA4::Ws only connects to I2s3!"); };
template<> struct SignalConnection<DataA4::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA4::Ch2, Peripheral::Tim3> { static constexpr int8_t af = 2; };
template<> struct SignalConnection<DataA4::Ck, Peripheral::Usart2> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataA4::Fsb, Peripheral::Sai1> { static constexpr int8_t af = 13; };
template<> struct SignalConnection<DataA4::In17, Peripheral::Adc2> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA4::Inm, Peripheral::Comp1> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA4::Nss, Peripheral::Spi1> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataA4::Nss, Peripheral::Spi3> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataA4::Out1, Peripheral::Dac1> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA4::Ws, Peripheral::I2s3> { static constexpr int8_t af = 6; };
template<> constexpr int8_t AdcChannel<DataA4, Peripheral::Adc2> = 17;
template<> constexpr int8_t DacChannel<DataA4, Peripheral::Dac1> = 1;

struct DataA5 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 5;
	struct BitBang { using Data = DataA5; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ch1 { using Data = DataA5; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1; };
	struct Etr { using Data = DataA5; static constexpr Gpio::Signal Signal = Gpio::Signal::Etr; };
	struct Frstx1 { using Data = DataA5; static constexpr Gpio::Signal Signal = Gpio::Signal::Frstx1; };
	struct Frstx2 { using Data = DataA5; static constexpr Gpio::Signal Signal = Gpio::Signal::Frstx2; };
	struct In13 { using Data = DataA5; static constexpr Gpio::Signal Signal = Gpio::Signal::In13; };
	struct Inm { using Data = DataA5; static constexpr Gpio::Signal Signal = Gpio::Signal::Inm; };
	struct Out2 { using Data = DataA5; static constexpr Gpio::Signal Signal = Gpio::Signal::Out2; };
	struct Sck { using Data = DataA5; static constexpr Gpio::Signal Signal = Gpio::Signal::Sck; };
	struct Vinm { using Data = DataA5; static constexpr Gpio::Signal Signal = Gpio::Signal::Vinm; };
	struct Vinm0 { using Data = DataA5; static constexpr Gpio::Signal Signal = Gpio::Signal::Vinm0; };
	struct Vinmsec { using Data = DataA5; static constexpr Gpio::Signal Signal = Gpio::Signal::Vinmsec; };
};
template<Peripheral p> struct SignalConnection<DataA5::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA5::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA5::Ch1, p> {
	static_assert((p == Peripheral::Tim2),"GpioA5::Ch1 only connects to Tim2!"); };
template<Peripheral p> struct SignalConnection<DataA5::Etr, p> {
	static_assert((p == Peripheral::Tim2),"GpioA5::Etr only connects to Tim2!"); };
template<Peripheral p> struct SignalConnection<DataA5::Frstx1, p> {
	static_assert((p == Peripheral::Ucpd1),"GpioA5::Frstx1 only connects to Ucpd1!"); };
template<Peripheral p> struct SignalConnection<DataA5::Frstx2, p> {
	static_assert((p == Peripheral::Ucpd1),"GpioA5::Frstx2 only connects to Ucpd1!"); };
template<Peripheral p> struct SignalConnection<DataA5::In13, p> {
	static_assert((p == Peripheral::Adc2),"GpioA5::In13 only connects to Adc2!"); };
template<Peripheral p> struct SignalConnection<DataA5::Inm, p> {
	static_assert((p == Peripheral::Comp2),"GpioA5::Inm only connects to Comp2!"); };
template<Peripheral p> struct SignalConnection<DataA5::Out2, p> {
	static_assert((p == Peripheral::Dac1),"GpioA5::Out2 only connects to Dac1!"); };
template<Peripheral p> struct SignalConnection<DataA5::Sck, p> {
	static_assert((p == Peripheral::Spi1),"GpioA5::Sck only connects to Spi1!"); };
template<Peripheral p> struct SignalConnection<DataA5::Vinm, p> {
	static_assert((p == Peripheral::Opamp2),"GpioA5::Vinm only connects to Opamp2!"); };
template<Peripheral p> struct SignalConnection<DataA5::Vinm0, p> {
	static_assert((p == Peripheral::Opamp2),"GpioA5::Vinm0 only connects to Opamp2!"); };
template<Peripheral p> struct SignalConnection<DataA5::Vinmsec, p> {
	static_assert((p == Peripheral::Opamp2),"GpioA5::Vinmsec only connects to Opamp2!"); };
template<> struct SignalConnection<DataA5::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA5::Ch1, Peripheral::Tim2> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataA5::Etr, Peripheral::Tim2> { static constexpr int8_t af = 2; };
template<> struct SignalConnection<DataA5::Frstx1, Peripheral::Ucpd1> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataA5::Frstx2, Peripheral::Ucpd1> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataA5::In13, Peripheral::Adc2> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA5::Inm, Peripheral::Comp2> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA5::Out2, Peripheral::Dac1> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA5::Sck, Peripheral::Spi1> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataA5::Vinm, Peripheral::Opamp2> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA5::Vinm0, Peripheral::Opamp2> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA5::Vinmsec, Peripheral::Opamp2> { static constexpr int8_t af = -1; };
template<> constexpr int8_t AdcChannel<DataA5, Peripheral::Adc2> = 13;
template<> constexpr int8_t DacChannel<DataA5, Peripheral::Dac1> = 2;

struct DataA6 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 6;
	struct BitBang { using Data = DataA6; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Bkin { using Data = DataA6; static constexpr Gpio::Signal Signal = Gpio::Signal::Bkin; };
	struct Ch1 { using Data = DataA6; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1; };
	struct Cts { using Data = DataA6; static constexpr Gpio::Signal Signal = Gpio::Signal::Cts; };
	struct In3 { using Data = DataA6; static constexpr Gpio::Signal Signal = Gpio::Signal::In3; };
	struct Miso { using Data = DataA6; static constexpr Gpio::Signal Signal = Gpio::Signal::Miso; };
	struct Out { using Data = DataA6; static constexpr Gpio::Signal Signal = Gpio::Signal::Out; };
	struct Vout { using Data = DataA6; static constexpr Gpio::Signal Signal = Gpio::Signal::Vout; };
};
template<Peripheral p> struct SignalConnection<DataA6::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA6::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA6::Bkin, p> {
	static_assert((p == Peripheral::Tim8) or (p == Peripheral::Tim1),
		"GpioA6::Bkin only connects to Tim8 or Tim1!"); };
template<Peripheral p> struct SignalConnection<DataA6::Ch1, p> {
	static_assert((p == Peripheral::Tim16) or (p == Peripheral::Tim3),
		"GpioA6::Ch1 only connects to Tim16 or Tim3!"); };
template<Peripheral p> struct SignalConnection<DataA6::Cts, p> {
	static_assert((p == Peripheral::Lpuart1),"GpioA6::Cts only connects to Lpuart1!"); };
template<Peripheral p> struct SignalConnection<DataA6::In3, p> {
	static_assert((p == Peripheral::Adc2),"GpioA6::In3 only connects to Adc2!"); };
template<Peripheral p> struct SignalConnection<DataA6::Miso, p> {
	static_assert((p == Peripheral::Spi1),"GpioA6::Miso only connects to Spi1!"); };
template<Peripheral p> struct SignalConnection<DataA6::Out, p> {
	static_assert((p == Peripheral::Comp1),"GpioA6::Out only connects to Comp1!"); };
template<Peripheral p> struct SignalConnection<DataA6::Vout, p> {
	static_assert((p == Peripheral::Opamp2),"GpioA6::Vout only connects to Opamp2!"); };
template<> struct SignalConnection<DataA6::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA6::Bkin, Peripheral::Tim8> { static constexpr int8_t af = 4; };
template<> struct SignalConnection<DataA6::Bkin, Peripheral::Tim1> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataA6::Ch1, Peripheral::Tim16> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataA6::Ch1, Peripheral::Tim3> { static constexpr int8_t af = 2; };
template<> struct SignalConnection<DataA6::Cts, Peripheral::Lpuart1> { static constexpr int8_t af = 12; };
template<> struct SignalConnection<DataA6::In3, Peripheral::Adc2> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA6::Miso, Peripheral::Spi1> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataA6::Out, Peripheral::Comp1> { static constexpr int8_t af = 8; };
template<> struct SignalConnection<DataA6::Vout, Peripheral::Opamp2> { static constexpr int8_t af = -1; };
template<> constexpr int8_t AdcChannel<DataA6, Peripheral::Adc2> = 3;

struct DataA7 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 7;
	struct BitBang { using Data = DataA7; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ch1 { using Data = DataA7; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1; };
	struct Ch1n { using Data = DataA7; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1n; };
	struct Ch2 { using Data = DataA7; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2; };
	struct Frstx1 { using Data = DataA7; static constexpr Gpio::Signal Signal = Gpio::Signal::Frstx1; };
	struct Frstx2 { using Data = DataA7; static constexpr Gpio::Signal Signal = Gpio::Signal::Frstx2; };
	struct In4 { using Data = DataA7; static constexpr Gpio::Signal Signal = Gpio::Signal::In4; };
	struct Inp { using Data = DataA7; static constexpr Gpio::Signal Signal = Gpio::Signal::Inp; };
	struct Mosi { using Data = DataA7; static constexpr Gpio::Signal Signal = Gpio::Signal::Mosi; };
	struct Out { using Data = DataA7; static constexpr Gpio::Signal Signal = Gpio::Signal::Out; };
	struct Vinp { using Data = DataA7; static constexpr Gpio::Signal Signal = Gpio::Signal::Vinp; };
	struct Vinpsec { using Data = DataA7; static constexpr Gpio::Signal Signal = Gpio::Signal::Vinpsec; };
};
template<Peripheral p> struct SignalConnection<DataA7::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA7::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA7::Ch1, p> {
	static_assert((p == Peripheral::Tim17),"GpioA7::Ch1 only connects to Tim17!"); };
template<Peripheral p> struct SignalConnection<DataA7::Ch1n, p> {
	static_assert((p == Peripheral::Tim8) or (p == Peripheral::Tim1),
		"GpioA7::Ch1n only connects to Tim8 or Tim1!"); };
template<Peripheral p> struct SignalConnection<DataA7::Ch2, p> {
	static_assert((p == Peripheral::Tim3),"GpioA7::Ch2 only connects to Tim3!"); };
template<Peripheral p> struct SignalConnection<DataA7::Frstx1, p> {
	static_assert((p == Peripheral::Ucpd1),"GpioA7::Frstx1 only connects to Ucpd1!"); };
template<Peripheral p> struct SignalConnection<DataA7::Frstx2, p> {
	static_assert((p == Peripheral::Ucpd1),"GpioA7::Frstx2 only connects to Ucpd1!"); };
template<Peripheral p> struct SignalConnection<DataA7::In4, p> {
	static_assert((p == Peripheral::Adc2),"GpioA7::In4 only connects to Adc2!"); };
template<Peripheral p> struct SignalConnection<DataA7::Inp, p> {
	static_assert((p == Peripheral::Comp2),"GpioA7::Inp only connects to Comp2!"); };
template<Peripheral p> struct SignalConnection<DataA7::Mosi, p> {
	static_assert((p == Peripheral::Spi1),"GpioA7::Mosi only connects to Spi1!"); };
template<Peripheral p> struct SignalConnection<DataA7::Out, p> {
	static_assert((p == Peripheral::Comp2),"GpioA7::Out only connects to Comp2!"); };
template<Peripheral p> struct SignalConnection<DataA7::Vinp, p> {
	static_assert((p == Peripheral::Opamp1) or (p == Peripheral::Opamp2),
		"GpioA7::Vinp only connects to Opamp1 or Opamp2!"); };
template<Peripheral p> struct SignalConnection<DataA7::Vinpsec, p> {
	static_assert((p == Peripheral::Opamp1) or (p == Peripheral::Opamp2),
		"GpioA7::Vinpsec only connects to Opamp1 or Opamp2!"); };
template<> struct SignalConnection<DataA7::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA7::Ch1, Peripheral::Tim17> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataA7::Ch1n, Peripheral::Tim8> { static constexpr int8_t af = 4; };
template<> struct SignalConnection<DataA7::Ch1n, Peripheral::Tim1> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataA7::Ch2, Peripheral::Tim3> { static constexpr int8_t af = 2; };
template<> struct SignalConnection<DataA7::Frstx1, Peripheral::Ucpd1> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataA7::Frstx2, Peripheral::Ucpd1> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataA7::In4, Peripheral::Adc2> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA7::Inp, Peripheral::Comp2> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataA7::Mosi, Peripheral::Spi1> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataA7::Out, Peripheral::Comp2> { static constexpr int8_t af = 8; };
template<> struct SignalConnection<DataA7::Vinp, Peripheral::Opamp1> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA7::Vinp, Peripheral::Opamp2> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA7::Vinpsec, Peripheral::Opamp1> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA7::Vinpsec, Peripheral::Opamp2> { static constexpr int8_t af = -1; };
template<> constexpr int8_t AdcChannel<DataA7, Peripheral::Adc2> = 4;

struct DataA8 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 8;
	struct BitBang { using Data = DataA8; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ch1 { using Data = DataA8; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1; };
	struct Ck { using Data = DataA8; static constexpr Gpio::Signal Signal = Gpio::Signal::Ck; };
	struct Ck2 { using Data = DataA8; static constexpr Gpio::Signal Signal = Gpio::Signal::Ck2; };
	struct Etr { using Data = DataA8; static constexpr Gpio::Signal Signal = Gpio::Signal::Etr; };
	struct Mck { using Data = DataA8; static constexpr Gpio::Signal Signal = Gpio::Signal::Mck; };
	struct Mco { using Data = DataA8; static constexpr Gpio::Signal Signal = Gpio::Signal::Mco; };
	struct Scka { using Data = DataA8; static constexpr Gpio::Signal Signal = Gpio::Signal::Scka; };
	struct Scl { using Data = DataA8; static constexpr Gpio::Signal Signal = Gpio::Signal::Scl; };
	struct Sda { using Data = DataA8; static constexpr Gpio::Signal Signal = Gpio::Signal::Sda; };
};
template<Peripheral p> struct SignalConnection<DataA8::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA8::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA8::Ch1, p> {
	static_assert((p == Peripheral::Tim1),"GpioA8::Ch1 only connects to Tim1!"); };
template<Peripheral p> struct SignalConnection<DataA8::Ck, p> {
	static_assert((p == Peripheral::Usart1),"GpioA8::Ck only connects to Usart1!"); };
template<Peripheral p> struct SignalConnection<DataA8::Ck2, p> {
	static_assert((p == Peripheral::Sai1),"GpioA8::Ck2 only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataA8::Etr, p> {
	static_assert((p == Peripheral::Tim4),"GpioA8::Etr only connects to Tim4!"); };
template<Peripheral p> struct SignalConnection<DataA8::Mck, p> {
	static_assert((p == Peripheral::I2s2),"GpioA8::Mck only connects to I2s2!"); };
template<Peripheral p> struct SignalConnection<DataA8::Mco, p> {
	static_assert((p == Peripheral::Rcc),"GpioA8::Mco only connects to Rcc!"); };
template<Peripheral p> struct SignalConnection<DataA8::Scka, p> {
	static_assert((p == Peripheral::Sai1),"GpioA8::Scka only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataA8::Scl, p> {
	static_assert((p == Peripheral::I2c3),"GpioA8::Scl only connects to I2c3!"); };
template<Peripheral p> struct SignalConnection<DataA8::Sda, p> {
	static_assert((p == Peripheral::I2c2),"GpioA8::Sda only connects to I2c2!"); };
template<> struct SignalConnection<DataA8::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA8::Ch1, Peripheral::Tim1> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataA8::Ck, Peripheral::Usart1> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataA8::Ck2, Peripheral::Sai1> { static constexpr int8_t af = 12; };
template<> struct SignalConnection<DataA8::Etr, Peripheral::Tim4> { static constexpr int8_t af = 10; };
template<> struct SignalConnection<DataA8::Mck, Peripheral::I2s2> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataA8::Mco, Peripheral::Rcc> { static constexpr int8_t af = 0; };
template<> struct SignalConnection<DataA8::Scka, Peripheral::Sai1> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataA8::Scl, Peripheral::I2c3> { static constexpr int8_t af = 2; };
template<> struct SignalConnection<DataA8::Sda, Peripheral::I2c2> { static constexpr int8_t af = 4; };

struct DataA9 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 9;
	struct BitBang { using Data = DataA9; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Bkin { using Data = DataA9; static constexpr Gpio::Signal Signal = Gpio::Signal::Bkin; };
	struct Ch2 { using Data = DataA9; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2; };
	struct Ch3 { using Data = DataA9; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch3; };
	struct Dbcc1 { using Data = DataA9; static constexpr Gpio::Signal Signal = Gpio::Signal::Dbcc1; };
	struct Fsa { using Data = DataA9; static constexpr Gpio::Signal Signal = Gpio::Signal::Fsa; };
	struct Mck { using Data = DataA9; static constexpr Gpio::Signal Signal = Gpio::Signal::Mck; };
	struct Scl { using Data = DataA9; static constexpr Gpio::Signal Signal = Gpio::Signal::Scl; };
	struct Smba { using Data = DataA9; static constexpr Gpio::Signal Signal = Gpio::Signal::Smba; };
	struct Tx { using Data = DataA9; static constexpr Gpio::Signal Signal = Gpio::Signal::Tx; };
};
template<Peripheral p> struct SignalConnection<DataA9::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA9::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA9::Bkin, p> {
	static_assert((p == Peripheral::Tim15),"GpioA9::Bkin only connects to Tim15!"); };
template<Peripheral p> struct SignalConnection<DataA9::Ch2, p> {
	static_assert((p == Peripheral::Tim1),"GpioA9::Ch2 only connects to Tim1!"); };
template<Peripheral p> struct SignalConnection<DataA9::Ch3, p> {
	static_assert((p == Peripheral::Tim2),"GpioA9::Ch3 only connects to Tim2!"); };
template<Peripheral p> struct SignalConnection<DataA9::Dbcc1, p> {
	static_assert((p == Peripheral::Ucpd1),"GpioA9::Dbcc1 only connects to Ucpd1!"); };
template<Peripheral p> struct SignalConnection<DataA9::Fsa, p> {
	static_assert((p == Peripheral::Sai1),"GpioA9::Fsa only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataA9::Mck, p> {
	static_assert((p == Peripheral::I2s3),"GpioA9::Mck only connects to I2s3!"); };
template<Peripheral p> struct SignalConnection<DataA9::Scl, p> {
	static_assert((p == Peripheral::I2c2),"GpioA9::Scl only connects to I2c2!"); };
template<Peripheral p> struct SignalConnection<DataA9::Smba, p> {
	static_assert((p == Peripheral::I2c3),"GpioA9::Smba only connects to I2c3!"); };
template<Peripheral p> struct SignalConnection<DataA9::Tx, p> {
	static_assert((p == Peripheral::Usart1),"GpioA9::Tx only connects to Usart1!"); };
template<> struct SignalConnection<DataA9::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA9::Bkin, Peripheral::Tim15> { static constexpr int8_t af = 9; };
template<> struct SignalConnection<DataA9::Ch2, Peripheral::Tim1> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataA9::Ch3, Peripheral::Tim2> { static constexpr int8_t af = 10; };
template<> struct SignalConnection<DataA9::Dbcc1, Peripheral::Ucpd1> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA9::Fsa, Peripheral::Sai1> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataA9::Mck, Peripheral::I2s3> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataA9::Scl, Peripheral::I2c2> { static constexpr int8_t af = 4; };
template<> struct SignalConnection<DataA9::Smba, Peripheral::I2c3> { static constexpr int8_t af = 2; };
template<> struct SignalConnection<DataA9::Tx, Peripheral::Usart1> { static constexpr int8_t af = 7; };

struct DataA10 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 10;
	struct BitBang { using Data = DataA10; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Bkin { using Data = DataA10; static constexpr Gpio::Signal Signal = Gpio::Signal::Bkin; };
	struct Ch3 { using Data = DataA10; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch3; };
	struct Ch4 { using Data = DataA10; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch4; };
	struct Crssync { using Data = DataA10; static constexpr Gpio::Signal Signal = Gpio::Signal::Crssync; };
	struct D1 { using Data = DataA10; static constexpr Gpio::Signal Signal = Gpio::Signal::D1; };
	struct Dbcc2 { using Data = DataA10; static constexpr Gpio::Signal Signal = Gpio::Signal::Dbcc2; };
	struct Miso { using Data = DataA10; static constexpr Gpio::Signal Signal = Gpio::Signal::Miso; };
	struct Rx { using Data = DataA10; static constexpr Gpio::Signal Signal = Gpio::Signal::Rx; };
	struct Sda { using Data = DataA10; static constexpr Gpio::Signal Signal = Gpio::Signal::Sda; };
	struct Smba { using Data = DataA10; static constexpr Gpio::Signal Signal = Gpio::Signal::Smba; };
};
template<Peripheral p> struct SignalConnection<DataA10::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA10::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA10::Bkin, p> {
	static_assert((p == Peripheral::Tim17) or (p == Peripheral::Tim8),
		"GpioA10::Bkin only connects to Tim17 or Tim8!"); };
template<Peripheral p> struct SignalConnection<DataA10::Ch3, p> {
	static_assert((p == Peripheral::Tim1),"GpioA10::Ch3 only connects to Tim1!"); };
template<Peripheral p> struct SignalConnection<DataA10::Ch4, p> {
	static_assert((p == Peripheral::Tim2),"GpioA10::Ch4 only connects to Tim2!"); };
template<Peripheral p> struct SignalConnection<DataA10::Crssync, p> {
	static_assert((p == Peripheral::Rcc),"GpioA10::Crssync only connects to Rcc!"); };
template<Peripheral p> struct SignalConnection<DataA10::D1, p> {
	static_assert((p == Peripheral::Sai1),"GpioA10::D1 only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataA10::Dbcc2, p> {
	static_assert((p == Peripheral::Ucpd1),"GpioA10::Dbcc2 only connects to Ucpd1!"); };
template<Peripheral p> struct SignalConnection<DataA10::Miso, p> {
	static_assert((p == Peripheral::Spi2),"GpioA10::Miso only connects to Spi2!"); };
template<Peripheral p> struct SignalConnection<DataA10::Rx, p> {
	static_assert((p == Peripheral::Usart1),"GpioA10::Rx only connects to Usart1!"); };
template<Peripheral p> struct SignalConnection<DataA10::Sda, p> {
	static_assert((p == Peripheral::Sai1),"GpioA10::Sda only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataA10::Smba, p> {
	static_assert((p == Peripheral::I2c2),"GpioA10::Smba only connects to I2c2!"); };
template<> struct SignalConnection<DataA10::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA10::Bkin, Peripheral::Tim17> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataA10::Bkin, Peripheral::Tim8> { static constexpr int8_t af = 11; };
template<> struct SignalConnection<DataA10::Ch3, Peripheral::Tim1> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataA10::Ch4, Peripheral::Tim2> { static constexpr int8_t af = 10; };
template<> struct SignalConnection<DataA10::Crssync, Peripheral::Rcc> { static constexpr int8_t af = 3; };
template<> struct SignalConnection<DataA10::D1, Peripheral::Sai1> { static constexpr int8_t af = 12; };
template<> struct SignalConnection<DataA10::Dbcc2, Peripheral::Ucpd1> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA10::Miso, Peripheral::Spi2> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataA10::Rx, Peripheral::Usart1> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataA10::Sda, Peripheral::Sai1> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataA10::Smba, Peripheral::I2c2> { static constexpr int8_t af = 4; };

struct DataA11 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 11;
	struct BitBang { using Data = DataA11; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Bkin2 { using Data = DataA11; static constexpr Gpio::Signal Signal = Gpio::Signal::Bkin2; };
	struct Ch1 { using Data = DataA11; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1; };
	struct Ch1n { using Data = DataA11; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1n; };
	struct Ch4 { using Data = DataA11; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch4; };
	struct Cts { using Data = DataA11; static constexpr Gpio::Signal Signal = Gpio::Signal::Cts; };
	struct Dm { using Data = DataA11; static constexpr Gpio::Signal Signal = Gpio::Signal::Dm; };
	struct Mosi { using Data = DataA11; static constexpr Gpio::Signal Signal = Gpio::Signal::Mosi; };
	struct Nss { using Data = DataA11; static constexpr Gpio::Signal Signal = Gpio::Signal::Nss; };
	struct Out { using Data = DataA11; static constexpr Gpio::Signal Signal = Gpio::Signal::Out; };
	struct Rx { using Data = DataA11; static constexpr Gpio::Signal Signal = Gpio::Signal::Rx; };
	struct Sd { using Data = DataA11; static constexpr Gpio::Signal Signal = Gpio::Signal::Sd; };
};
template<Peripheral p> struct SignalConnection<DataA11::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA11::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA11::Bkin2, p> {
	static_assert((p == Peripheral::Tim1),"GpioA11::Bkin2 only connects to Tim1!"); };
template<Peripheral p> struct SignalConnection<DataA11::Ch1, p> {
	static_assert((p == Peripheral::Tim4),"GpioA11::Ch1 only connects to Tim4!"); };
template<Peripheral p> struct SignalConnection<DataA11::Ch1n, p> {
	static_assert((p == Peripheral::Tim1),"GpioA11::Ch1n only connects to Tim1!"); };
template<Peripheral p> struct SignalConnection<DataA11::Ch4, p> {
	static_assert((p == Peripheral::Tim1),"GpioA11::Ch4 only connects to Tim1!"); };
template<Peripheral p> struct SignalConnection<DataA11::Cts, p> {
	static_assert((p == Peripheral::Usart1),"GpioA11::Cts only connects to Usart1!"); };
template<Peripheral p> struct SignalConnection<DataA11::Dm, p> {
	static_assert((p == Peripheral::Usb),"GpioA11::Dm only connects to Usb!"); };
template<Peripheral p> struct SignalConnection<DataA11::Mosi, p> {
	static_assert((p == Peripheral::Spi2),"GpioA11::Mosi only connects to Spi2!"); };
template<Peripheral p> struct SignalConnection<DataA11::Nss, p> {
	static_assert((p == Peripheral::Usart1),"GpioA11::Nss only connects to Usart1!"); };
template<Peripheral p> struct SignalConnection<DataA11::Out, p> {
	static_assert((p == Peripheral::Comp1),"GpioA11::Out only connects to Comp1!"); };
template<Peripheral p> struct SignalConnection<DataA11::Rx, p> {
	static_assert((p == Peripheral::Fdcan1),"GpioA11::Rx only connects to Fdcan1!"); };
template<Peripheral p> struct SignalConnection<DataA11::Sd, p> {
	static_assert((p == Peripheral::I2s2),"GpioA11::Sd only connects to I2s2!"); };
template<> struct SignalConnection<DataA11::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA11::Bkin2, Peripheral::Tim1> { static constexpr int8_t af = 12; };
template<> struct SignalConnection<DataA11::Ch1, Peripheral::Tim4> { static constexpr int8_t af = 10; };
template<> struct SignalConnection<DataA11::Ch1n, Peripheral::Tim1> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataA11::Ch4, Peripheral::Tim1> { static constexpr int8_t af = 11; };
template<> struct SignalConnection<DataA11::Cts, Peripheral::Usart1> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataA11::Dm, Peripheral::Usb> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA11::Mosi, Peripheral::Spi2> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataA11::Nss, Peripheral::Usart1> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataA11::Out, Peripheral::Comp1> { static constexpr int8_t af = 8; };
template<> struct SignalConnection<DataA11::Rx, Peripheral::Fdcan1> { static constexpr int8_t af = 9; };
template<> struct SignalConnection<DataA11::Sd, Peripheral::I2s2> { static constexpr int8_t af = 5; };

struct DataA12 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 12;
	struct BitBang { using Data = DataA12; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ch1 { using Data = DataA12; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1; };
	struct Ch2 { using Data = DataA12; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2; };
	struct Ch2n { using Data = DataA12; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2n; };
	struct Ckin { using Data = DataA12; static constexpr Gpio::Signal Signal = Gpio::Signal::Ckin; };
	struct De { using Data = DataA12; static constexpr Gpio::Signal Signal = Gpio::Signal::De; };
	struct Dp { using Data = DataA12; static constexpr Gpio::Signal Signal = Gpio::Signal::Dp; };
	struct Etr { using Data = DataA12; static constexpr Gpio::Signal Signal = Gpio::Signal::Etr; };
	struct Out { using Data = DataA12; static constexpr Gpio::Signal Signal = Gpio::Signal::Out; };
	struct Rts { using Data = DataA12; static constexpr Gpio::Signal Signal = Gpio::Signal::Rts; };
	struct Tx { using Data = DataA12; static constexpr Gpio::Signal Signal = Gpio::Signal::Tx; };
};
template<Peripheral p> struct SignalConnection<DataA12::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA12::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA12::Ch1, p> {
	static_assert((p == Peripheral::Tim16),"GpioA12::Ch1 only connects to Tim16!"); };
template<Peripheral p> struct SignalConnection<DataA12::Ch2, p> {
	static_assert((p == Peripheral::Tim4),"GpioA12::Ch2 only connects to Tim4!"); };
template<Peripheral p> struct SignalConnection<DataA12::Ch2n, p> {
	static_assert((p == Peripheral::Tim1),"GpioA12::Ch2n only connects to Tim1!"); };
template<Peripheral p> struct SignalConnection<DataA12::Ckin, p> {
	static_assert((p == Peripheral::I2s),"GpioA12::Ckin only connects to I2s!"); };
template<Peripheral p> struct SignalConnection<DataA12::De, p> {
	static_assert((p == Peripheral::Usart1),"GpioA12::De only connects to Usart1!"); };
template<Peripheral p> struct SignalConnection<DataA12::Dp, p> {
	static_assert((p == Peripheral::Usb),"GpioA12::Dp only connects to Usb!"); };
template<Peripheral p> struct SignalConnection<DataA12::Etr, p> {
	static_assert((p == Peripheral::Tim1),"GpioA12::Etr only connects to Tim1!"); };
template<Peripheral p> struct SignalConnection<DataA12::Out, p> {
	static_assert((p == Peripheral::Comp2),"GpioA12::Out only connects to Comp2!"); };
template<Peripheral p> struct SignalConnection<DataA12::Rts, p> {
	static_assert((p == Peripheral::Usart1),"GpioA12::Rts only connects to Usart1!"); };
template<Peripheral p> struct SignalConnection<DataA12::Tx, p> {
	static_assert((p == Peripheral::Fdcan1),"GpioA12::Tx only connects to Fdcan1!"); };
template<> struct SignalConnection<DataA12::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA12::Ch1, Peripheral::Tim16> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataA12::Ch2, Peripheral::Tim4> { static constexpr int8_t af = 10; };
template<> struct SignalConnection<DataA12::Ch2n, Peripheral::Tim1> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataA12::Ckin, Peripheral::I2s> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataA12::De, Peripheral::Usart1> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataA12::Dp, Peripheral::Usb> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA12::Etr, Peripheral::Tim1> { static constexpr int8_t af = 11; };
template<> struct SignalConnection<DataA12::Out, Peripheral::Comp2> { static constexpr int8_t af = 8; };
template<> struct SignalConnection<DataA12::Rts, Peripheral::Usart1> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataA12::Tx, Peripheral::Fdcan1> { static constexpr int8_t af = 9; };

struct DataA13 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 13;
	struct BitBang { using Data = DataA13; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ch1n { using Data = DataA13; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1n; };
	struct Ch3 { using Data = DataA13; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch3; };
	struct Jtms { using Data = DataA13; static constexpr Gpio::Signal Signal = Gpio::Signal::Jtms; };
	struct Out { using Data = DataA13; static constexpr Gpio::Signal Signal = Gpio::Signal::Out; };
	struct Scl { using Data = DataA13; static constexpr Gpio::Signal Signal = Gpio::Signal::Scl; };
	struct Sdb { using Data = DataA13; static constexpr Gpio::Signal Signal = Gpio::Signal::Sdb; };
	struct Swdio { using Data = DataA13; static constexpr Gpio::Signal Signal = Gpio::Signal::Swdio; };
};
template<Peripheral p> struct SignalConnection<DataA13::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA13::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA13::Ch1n, p> {
	static_assert((p == Peripheral::Tim16),"GpioA13::Ch1n only connects to Tim16!"); };
template<Peripheral p> struct SignalConnection<DataA13::Ch3, p> {
	static_assert((p == Peripheral::Tim4),"GpioA13::Ch3 only connects to Tim4!"); };
template<Peripheral p> struct SignalConnection<DataA13::Jtms, p> {
	static_assert((p == Peripheral::Sys),"GpioA13::Jtms only connects to Sys!"); };
template<Peripheral p> struct SignalConnection<DataA13::Out, p> {
	static_assert((p == Peripheral::Irtim),"GpioA13::Out only connects to Irtim!"); };
template<Peripheral p> struct SignalConnection<DataA13::Scl, p> {
	static_assert((p == Peripheral::I2c1),"GpioA13::Scl only connects to I2c1!"); };
template<Peripheral p> struct SignalConnection<DataA13::Sdb, p> {
	static_assert((p == Peripheral::Sai1),"GpioA13::Sdb only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataA13::Swdio, p> {
	static_assert((p == Peripheral::Sys),"GpioA13::Swdio only connects to Sys!"); };
template<> struct SignalConnection<DataA13::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA13::Ch1n, Peripheral::Tim16> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataA13::Ch3, Peripheral::Tim4> { static constexpr int8_t af = 10; };
template<> struct SignalConnection<DataA13::Jtms, Peripheral::Sys> { static constexpr int8_t af = 0; };
template<> struct SignalConnection<DataA13::Out, Peripheral::Irtim> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataA13::Scl, Peripheral::I2c1> { static constexpr int8_t af = 4; };
template<> struct SignalConnection<DataA13::Sdb, Peripheral::Sai1> { static constexpr int8_t af = 13; };
template<> struct SignalConnection<DataA13::Swdio, Peripheral::Sys> { static constexpr int8_t af = 0; };

struct DataA14 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 14;
	struct BitBang { using Data = DataA14; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Bkin { using Data = DataA14; static constexpr Gpio::Signal Signal = Gpio::Signal::Bkin; };
	struct Ch2 { using Data = DataA14; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2; };
	struct Fsb { using Data = DataA14; static constexpr Gpio::Signal Signal = Gpio::Signal::Fsb; };
	struct Jtck { using Data = DataA14; static constexpr Gpio::Signal Signal = Gpio::Signal::Jtck; };
	struct Out { using Data = DataA14; static constexpr Gpio::Signal Signal = Gpio::Signal::Out; };
	struct Sda { using Data = DataA14; static constexpr Gpio::Signal Signal = Gpio::Signal::Sda; };
	struct Swclk { using Data = DataA14; static constexpr Gpio::Signal Signal = Gpio::Signal::Swclk; };
	struct Tx { using Data = DataA14; static constexpr Gpio::Signal Signal = Gpio::Signal::Tx; };
};
template<Peripheral p> struct SignalConnection<DataA14::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA14::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA14::Bkin, p> {
	static_assert((p == Peripheral::Tim1),"GpioA14::Bkin only connects to Tim1!"); };
template<Peripheral p> struct SignalConnection<DataA14::Ch2, p> {
	static_assert((p == Peripheral::Tim8),"GpioA14::Ch2 only connects to Tim8!"); };
template<Peripheral p> struct SignalConnection<DataA14::Fsb, p> {
	static_assert((p == Peripheral::Sai1),"GpioA14::Fsb only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataA14::Jtck, p> {
	static_assert((p == Peripheral::Sys),"GpioA14::Jtck only connects to Sys!"); };
template<Peripheral p> struct SignalConnection<DataA14::Out, p> {
	static_assert((p == Peripheral::Lptim1),"GpioA14::Out only connects to Lptim1!"); };
template<Peripheral p> struct SignalConnection<DataA14::Sda, p> {
	static_assert((p == Peripheral::I2c1),"GpioA14::Sda only connects to I2c1!"); };
template<Peripheral p> struct SignalConnection<DataA14::Swclk, p> {
	static_assert((p == Peripheral::Sys),"GpioA14::Swclk only connects to Sys!"); };
template<Peripheral p> struct SignalConnection<DataA14::Tx, p> {
	static_assert((p == Peripheral::Usart2),"GpioA14::Tx only connects to Usart2!"); };
template<> struct SignalConnection<DataA14::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA14::Bkin, Peripheral::Tim1> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataA14::Ch2, Peripheral::Tim8> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataA14::Fsb, Peripheral::Sai1> { static constexpr int8_t af = 13; };
template<> struct SignalConnection<DataA14::Jtck, Peripheral::Sys> { static constexpr int8_t af = 0; };
template<> struct SignalConnection<DataA14::Out, Peripheral::Lptim1> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataA14::Sda, Peripheral::I2c1> { static constexpr int8_t af = 4; };
template<> struct SignalConnection<DataA14::Swclk, Peripheral::Sys> { static constexpr int8_t af = 0; };
template<> struct SignalConnection<DataA14::Tx, Peripheral::Usart2> { static constexpr int8_t af = 7; };

struct DataA15 {
	static constexpr Gpio::Port port = Gpio::Port::A;
	static constexpr uint8_t pin = 15;
	struct BitBang { using Data = DataA15; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Bkin { using Data = DataA15; static constexpr Gpio::Signal Signal = Gpio::Signal::Bkin; };
	struct Ch1 { using Data = DataA15; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1; };
	struct Etr { using Data = DataA15; static constexpr Gpio::Signal Signal = Gpio::Signal::Etr; };
	struct Jtdi { using Data = DataA15; static constexpr Gpio::Signal Signal = Gpio::Signal::Jtdi; };
	struct Nss { using Data = DataA15; static constexpr Gpio::Signal Signal = Gpio::Signal::Nss; };
	struct Rx { using Data = DataA15; static constexpr Gpio::Signal Signal = Gpio::Signal::Rx; };
	struct Scl { using Data = DataA15; static constexpr Gpio::Signal Signal = Gpio::Signal::Scl; };
	struct Ws { using Data = DataA15; static constexpr Gpio::Signal Signal = Gpio::Signal::Ws; };
};
template<Peripheral p> struct SignalConnection<DataA15::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioA15::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataA15::Bkin, p> {
	static_assert((p == Peripheral::Tim1),"GpioA15::Bkin only connects to Tim1!"); };
template<Peripheral p> struct SignalConnection<DataA15::Ch1, p> {
	static_assert((p == Peripheral::Tim2) or (p == Peripheral::Tim8),
		"GpioA15::Ch1 only connects to Tim2 or Tim8!"); };
template<Peripheral p> struct SignalConnection<DataA15::Etr, p> {
	static_assert((p == Peripheral::Tim2),"GpioA15::Etr only connects to Tim2!"); };
template<Peripheral p> struct SignalConnection<DataA15::Jtdi, p> {
	static_assert((p == Peripheral::Sys),"GpioA15::Jtdi only connects to Sys!"); };
template<Peripheral p> struct SignalConnection<DataA15::Nss, p> {
	static_assert((p == Peripheral::Spi1) or (p == Peripheral::Spi3),
		"GpioA15::Nss only connects to Spi1 or Spi3!"); };
template<Peripheral p> struct SignalConnection<DataA15::Rx, p> {
	static_assert((p == Peripheral::Usart2),"GpioA15::Rx only connects to Usart2!"); };
template<Peripheral p> struct SignalConnection<DataA15::Scl, p> {
	static_assert((p == Peripheral::I2c1),"GpioA15::Scl only connects to I2c1!"); };
template<Peripheral p> struct SignalConnection<DataA15::Ws, p> {
	static_assert((p == Peripheral::I2s3),"GpioA15::Ws only connects to I2s3!"); };
template<> struct SignalConnection<DataA15::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataA15::Bkin, Peripheral::Tim1> { static constexpr int8_t af = 9; };
template<> struct SignalConnection<DataA15::Ch1, Peripheral::Tim2> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataA15::Ch1, Peripheral::Tim8> { static constexpr int8_t af = 2; };
template<> struct SignalConnection<DataA15::Etr, Peripheral::Tim2> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataA15::Jtdi, Peripheral::Sys> { static constexpr int8_t af = 0; };
template<> struct SignalConnection<DataA15::Nss, Peripheral::Spi1> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataA15::Nss, Peripheral::Spi3> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataA15::Rx, Peripheral::Usart2> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataA15::Scl, Peripheral::I2c1> { static constexpr int8_t af = 4; };
template<> struct SignalConnection<DataA15::Ws, Peripheral::I2s3> { static constexpr int8_t af = 6; };

struct DataB0 {
	static constexpr Gpio::Port port = Gpio::Port::B;
	static constexpr uint8_t pin = 0;
	struct BitBang { using Data = DataB0; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ch2n { using Data = DataB0; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2n; };
	struct Ch3 { using Data = DataB0; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch3; };
	struct Frstx1 { using Data = DataB0; static constexpr Gpio::Signal Signal = Gpio::Signal::Frstx1; };
	struct Frstx2 { using Data = DataB0; static constexpr Gpio::Signal Signal = Gpio::Signal::Frstx2; };
	struct In15 { using Data = DataB0; static constexpr Gpio::Signal Signal = Gpio::Signal::In15; };
	struct Inp { using Data = DataB0; static constexpr Gpio::Signal Signal = Gpio::Signal::Inp; };
	struct Vinp { using Data = DataB0; static constexpr Gpio::Signal Signal = Gpio::Signal::Vinp; };
	struct Vinpsec { using Data = DataB0; static constexpr Gpio::Signal Signal = Gpio::Signal::Vinpsec; };
};
template<Peripheral p> struct SignalConnection<DataB0::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioB0::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataB0::Ch2n, p> {
	static_assert((p == Peripheral::Tim8) or (p == Peripheral::Tim1),
		"GpioB0::Ch2n only connects to Tim8 or Tim1!"); };
template<Peripheral p> struct SignalConnection<DataB0::Ch3, p> {
	static_assert((p == Peripheral::Tim3),"GpioB0::Ch3 only connects to Tim3!"); };
template<Peripheral p> struct SignalConnection<DataB0::Frstx1, p> {
	static_assert((p == Peripheral::Ucpd1),"GpioB0::Frstx1 only connects to Ucpd1!"); };
template<Peripheral p> struct SignalConnection<DataB0::Frstx2, p> {
	static_assert((p == Peripheral::Ucpd1),"GpioB0::Frstx2 only connects to Ucpd1!"); };
template<Peripheral p> struct SignalConnection<DataB0::In15, p> {
	static_assert((p == Peripheral::Adc1),"GpioB0::In15 only connects to Adc1!"); };
template<Peripheral p> struct SignalConnection<DataB0::Inp, p> {
	static_assert((p == Peripheral::Comp4),"GpioB0::Inp only connects to Comp4!"); };
template<Peripheral p> struct SignalConnection<DataB0::Vinp, p> {
	static_assert((p == Peripheral::Opamp2) or (p == Peripheral::Opamp3),
		"GpioB0::Vinp only connects to Opamp2 or Opamp3!"); };
template<Peripheral p> struct SignalConnection<DataB0::Vinpsec, p> {
	static_assert((p == Peripheral::Opamp2) or (p == Peripheral::Opamp3),
		"GpioB0::Vinpsec only connects to Opamp2 or Opamp3!"); };
template<> struct SignalConnection<DataB0::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataB0::Ch2n, Peripheral::Tim8> { static constexpr int8_t af = 4; };
template<> struct SignalConnection<DataB0::Ch2n, Peripheral::Tim1> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataB0::Ch3, Peripheral::Tim3> { static constexpr int8_t af = 2; };
template<> struct SignalConnection<DataB0::Frstx1, Peripheral::Ucpd1> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataB0::Frstx2, Peripheral::Ucpd1> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataB0::In15, Peripheral::Adc1> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataB0::Inp, Peripheral::Comp4> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataB0::Vinp, Peripheral::Opamp2> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataB0::Vinp, Peripheral::Opamp3> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataB0::Vinpsec, Peripheral::Opamp2> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataB0::Vinpsec, Peripheral::Opamp3> { static constexpr int8_t af = -1; };
template<> constexpr int8_t AdcChannel<DataB0, Peripheral::Adc1> = 15;

struct DataB3 {
	static constexpr Gpio::Port port = Gpio::Port::B;
	static constexpr uint8_t pin = 3;
	struct BitBang { using Data = DataB3; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ch1n { using Data = DataB3; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1n; };
	struct Ch2 { using Data = DataB3; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2; };
	struct Ck { using Data = DataB3; static constexpr Gpio::Signal Signal = Gpio::Signal::Ck; };
	struct Crssync { using Data = DataB3; static constexpr Gpio::Signal Signal = Gpio::Signal::Crssync; };
	struct Etr { using Data = DataB3; static constexpr Gpio::Signal Signal = Gpio::Signal::Etr; };
	struct Jtdo { using Data = DataB3; static constexpr Gpio::Signal Signal = Gpio::Signal::Jtdo; };
	struct Sck { using Data = DataB3; static constexpr Gpio::Signal Signal = Gpio::Signal::Sck; };
	struct Sckb { using Data = DataB3; static constexpr Gpio::Signal Signal = Gpio::Signal::Sckb; };
	struct Swo { using Data = DataB3; static constexpr Gpio::Signal Signal = Gpio::Signal::Swo; };
	struct Tx { using Data = DataB3; static constexpr Gpio::Signal Signal = Gpio::Signal::Tx; };
};
template<Peripheral p> struct SignalConnection<DataB3::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioB3::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataB3::Ch1n, p> {
	static_assert((p == Peripheral::Tim8),"GpioB3::Ch1n only connects to Tim8!"); };
template<Peripheral p> struct SignalConnection<DataB3::Ch2, p> {
	static_assert((p == Peripheral::Tim2),"GpioB3::Ch2 only connects to Tim2!"); };
template<Peripheral p> struct SignalConnection<DataB3::Ck, p> {
	static_assert((p == Peripheral::I2s3),"GpioB3::Ck only connects to I2s3!"); };
template<Peripheral p> struct SignalConnection<DataB3::Crssync, p> {
	static_assert((p == Peripheral::Rcc),"GpioB3::Crssync only connects to Rcc!"); };
template<Peripheral p> struct SignalConnection<DataB3::Etr, p> {
	static_assert((p == Peripheral::Tim4) or (p == Peripheral::Tim3),
		"GpioB3::Etr only connects to Tim4 or Tim3!"); };
template<Peripheral p> struct SignalConnection<DataB3::Jtdo, p> {
	static_assert((p == Peripheral::Sys),"GpioB3::Jtdo only connects to Sys!"); };
template<Peripheral p> struct SignalConnection<DataB3::Sck, p> {
	static_assert((p == Peripheral::Spi1) or (p == Peripheral::Spi3),
		"GpioB3::Sck only connects to Spi1 or Spi3!"); };
template<Peripheral p> struct SignalConnection<DataB3::Sckb, p> {
	static_assert((p == Peripheral::Sai1),"GpioB3::Sckb only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataB3::Swo, p> {
	static_assert((p == Peripheral::Sys),"GpioB3::Swo only connects to Sys!"); };
template<Peripheral p> struct SignalConnection<DataB3::Tx, p> {
	static_assert((p == Peripheral::Usart2),"GpioB3::Tx only connects to Usart2!"); };
template<> struct SignalConnection<DataB3::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataB3::Ch1n, Peripheral::Tim8> { static constexpr int8_t af = 4; };
template<> struct SignalConnection<DataB3::Ch2, Peripheral::Tim2> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataB3::Ck, Peripheral::I2s3> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataB3::Crssync, Peripheral::Rcc> { static constexpr int8_t af = 3; };
template<> struct SignalConnection<DataB3::Etr, Peripheral::Tim4> { static constexpr int8_t af = 2; };
template<> struct SignalConnection<DataB3::Etr, Peripheral::Tim3> { static constexpr int8_t af = 10; };
template<> struct SignalConnection<DataB3::Jtdo, Peripheral::Sys> { static constexpr int8_t af = 0; };
template<> struct SignalConnection<DataB3::Sck, Peripheral::Spi1> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataB3::Sck, Peripheral::Spi3> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataB3::Sckb, Peripheral::Sai1> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataB3::Swo, Peripheral::Sys> { static constexpr int8_t af = 0; };
template<> struct SignalConnection<DataB3::Tx, Peripheral::Usart2> { static constexpr int8_t af = 7; };

struct DataB4 {
	static constexpr Gpio::Port port = Gpio::Port::B;
	static constexpr uint8_t pin = 4;
	struct BitBang { using Data = DataB4; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Bkin { using Data = DataB4; static constexpr Gpio::Signal Signal = Gpio::Signal::Bkin; };
	struct Cc2 { using Data = DataB4; static constexpr Gpio::Signal Signal = Gpio::Signal::Cc2; };
	struct Ch1 { using Data = DataB4; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1; };
	struct Ch2n { using Data = DataB4; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2n; };
	struct Jtrst { using Data = DataB4; static constexpr Gpio::Signal Signal = Gpio::Signal::Jtrst; };
	struct Mclkb { using Data = DataB4; static constexpr Gpio::Signal Signal = Gpio::Signal::Mclkb; };
	struct Miso { using Data = DataB4; static constexpr Gpio::Signal Signal = Gpio::Signal::Miso; };
	struct Rx { using Data = DataB4; static constexpr Gpio::Signal Signal = Gpio::Signal::Rx; };
};
template<Peripheral p> struct SignalConnection<DataB4::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioB4::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataB4::Bkin, p> {
	static_assert((p == Peripheral::Tim17),"GpioB4::Bkin only connects to Tim17!"); };
template<Peripheral p> struct SignalConnection<DataB4::Cc2, p> {
	static_assert((p == Peripheral::Ucpd1),"GpioB4::Cc2 only connects to Ucpd1!"); };
template<Peripheral p> struct SignalConnection<DataB4::Ch1, p> {
	static_assert((p == Peripheral::Tim16) or (p == Peripheral::Tim3),
		"GpioB4::Ch1 only connects to Tim16 or Tim3!"); };
template<Peripheral p> struct SignalConnection<DataB4::Ch2n, p> {
	static_assert((p == Peripheral::Tim8),"GpioB4::Ch2n only connects to Tim8!"); };
template<Peripheral p> struct SignalConnection<DataB4::Jtrst, p> {
	static_assert((p == Peripheral::Sys),"GpioB4::Jtrst only connects to Sys!"); };
template<Peripheral p> struct SignalConnection<DataB4::Mclkb, p> {
	static_assert((p == Peripheral::Sai1),"GpioB4::Mclkb only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataB4::Miso, p> {
	static_assert((p == Peripheral::Spi1) or (p == Peripheral::Spi3),
		"GpioB4::Miso only connects to Spi1 or Spi3!"); };
template<Peripheral p> struct SignalConnection<DataB4::Rx, p> {
	static_assert((p == Peripheral::Usart2),"GpioB4::Rx only connects to Usart2!"); };
template<> struct SignalConnection<DataB4::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataB4::Bkin, Peripheral::Tim17> { static constexpr int8_t af = 10; };
template<> struct SignalConnection<DataB4::Cc2, Peripheral::Ucpd1> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataB4::Ch1, Peripheral::Tim16> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataB4::Ch1, Peripheral::Tim3> { static constexpr int8_t af = 2; };
template<> struct SignalConnection<DataB4::Ch2n, Peripheral::Tim8> { static constexpr int8_t af = 4; };
template<> struct SignalConnection<DataB4::Jtrst, Peripheral::Sys> { static constexpr int8_t af = 0; };
template<> struct SignalConnection<DataB4::Mclkb, Peripheral::Sai1> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataB4::Miso, Peripheral::Spi1> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataB4::Miso, Peripheral::Spi3> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataB4::Rx, Peripheral::Usart2> { static constexpr int8_t af = 7; };

struct DataB5 {
	static constexpr Gpio::Port port = Gpio::Port::B;
	static constexpr uint8_t pin = 5;
	struct BitBang { using Data = DataB5; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Bkin { using Data = DataB5; static constexpr Gpio::Signal Signal = Gpio::Signal::Bkin; };
	struct Ch1 { using Data = DataB5; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1; };
	struct Ch2 { using Data = DataB5; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2; };
	struct Ch3n { using Data = DataB5; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch3n; };
	struct Ck { using Data = DataB5; static constexpr Gpio::Signal Signal = Gpio::Signal::Ck; };
	struct In1 { using Data = DataB5; static constexpr Gpio::Signal Signal = Gpio::Signal::In1; };
	struct Mosi { using Data = DataB5; static constexpr Gpio::Signal Signal = Gpio::Signal::Mosi; };
	struct Sd { using Data = DataB5; static constexpr Gpio::Signal Signal = Gpio::Signal::Sd; };
	struct Sda { using Data = DataB5; static constexpr Gpio::Signal Signal = Gpio::Signal::Sda; };
	struct Sdb { using Data = DataB5; static constexpr Gpio::Signal Signal = Gpio::Signal::Sdb; };
	struct Smba { using Data = DataB5; static constexpr Gpio::Signal Signal = Gpio::Signal::Smba; };
};
template<Peripheral p> struct SignalConnection<DataB5::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioB5::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataB5::Bkin, p> {
	static_assert((p == Peripheral::Tim16),"GpioB5::Bkin only connects to Tim16!"); };
template<Peripheral p> struct SignalConnection<DataB5::Ch1, p> {
	static_assert((p == Peripheral::Tim17),"GpioB5::Ch1 only connects to Tim17!"); };
template<Peripheral p> struct SignalConnection<DataB5::Ch2, p> {
	static_assert((p == Peripheral::Tim3),"GpioB5::Ch2 only connects to Tim3!"); };
template<Peripheral p> struct SignalConnection<DataB5::Ch3n, p> {
	static_assert((p == Peripheral::Tim8),"GpioB5::Ch3n only connects to Tim8!"); };
template<Peripheral p> struct SignalConnection<DataB5::Ck, p> {
	static_assert((p == Peripheral::Usart2),"GpioB5::Ck only connects to Usart2!"); };
template<Peripheral p> struct SignalConnection<DataB5::In1, p> {
	static_assert((p == Peripheral::Lptim1),"GpioB5::In1 only connects to Lptim1!"); };
template<Peripheral p> struct SignalConnection<DataB5::Mosi, p> {
	static_assert((p == Peripheral::Spi1) or (p == Peripheral::Spi3),
		"GpioB5::Mosi only connects to Spi1 or Spi3!"); };
template<Peripheral p> struct SignalConnection<DataB5::Sd, p> {
	static_assert((p == Peripheral::I2s3),"GpioB5::Sd only connects to I2s3!"); };
template<Peripheral p> struct SignalConnection<DataB5::Sda, p> {
	static_assert((p == Peripheral::I2c3),"GpioB5::Sda only connects to I2c3!"); };
template<Peripheral p> struct SignalConnection<DataB5::Sdb, p> {
	static_assert((p == Peripheral::Sai1),"GpioB5::Sdb only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataB5::Smba, p> {
	static_assert((p == Peripheral::I2c1),"GpioB5::Smba only connects to I2c1!"); };
template<> struct SignalConnection<DataB5::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataB5::Bkin, Peripheral::Tim16> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataB5::Ch1, Peripheral::Tim17> { static constexpr int8_t af = 10; };
template<> struct SignalConnection<DataB5::Ch2, Peripheral::Tim3> { static constexpr int8_t af = 2; };
template<> struct SignalConnection<DataB5::Ch3n, Peripheral::Tim8> { static constexpr int8_t af = 3; };
template<> struct SignalConnection<DataB5::Ck, Peripheral::Usart2> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataB5::In1, Peripheral::Lptim1> { static constexpr int8_t af = 11; };
template<> struct SignalConnection<DataB5::Mosi, Peripheral::Spi1> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataB5::Mosi, Peripheral::Spi3> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataB5::Sd, Peripheral::I2s3> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataB5::Sda, Peripheral::I2c3> { static constexpr int8_t af = 8; };
template<> struct SignalConnection<DataB5::Sdb, Peripheral::Sai1> { static constexpr int8_t af = 12; };
template<> struct SignalConnection<DataB5::Smba, Peripheral::I2c1> { static constexpr int8_t af = 4; };

struct DataB6 {
	static constexpr Gpio::Port port = Gpio::Port::B;
	static constexpr uint8_t pin = 6;
	struct BitBang { using Data = DataB6; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Bkin2 { using Data = DataB6; static constexpr Gpio::Signal Signal = Gpio::Signal::Bkin2; };
	struct Cc1 { using Data = DataB6; static constexpr Gpio::Signal Signal = Gpio::Signal::Cc1; };
	struct Ch1 { using Data = DataB6; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1; };
	struct Ch1n { using Data = DataB6; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1n; };
	struct Etr { using Data = DataB6; static constexpr Gpio::Signal Signal = Gpio::Signal::Etr; };
	struct Fsb { using Data = DataB6; static constexpr Gpio::Signal Signal = Gpio::Signal::Fsb; };
	struct Out { using Data = DataB6; static constexpr Gpio::Signal Signal = Gpio::Signal::Out; };
	struct Tx { using Data = DataB6; static constexpr Gpio::Signal Signal = Gpio::Signal::Tx; };
};
template<Peripheral p> struct SignalConnection<DataB6::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioB6::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataB6::Bkin2, p> {
	static_assert((p == Peripheral::Tim8),"GpioB6::Bkin2 only connects to Tim8!"); };
template<Peripheral p> struct SignalConnection<DataB6::Cc1, p> {
	static_assert((p == Peripheral::Ucpd1),"GpioB6::Cc1 only connects to Ucpd1!"); };
template<Peripheral p> struct SignalConnection<DataB6::Ch1, p> {
	static_assert((p == Peripheral::Tim4) or (p == Peripheral::Tim8),
		"GpioB6::Ch1 only connects to Tim4 or Tim8!"); };
template<Peripheral p> struct SignalConnection<DataB6::Ch1n, p> {
	static_assert((p == Peripheral::Tim16),"GpioB6::Ch1n only connects to Tim16!"); };
template<Peripheral p> struct SignalConnection<DataB6::Etr, p> {
	static_assert((p == Peripheral::Tim8) or (p == Peripheral::Lptim1),
		"GpioB6::Etr only connects to Tim8 or Lptim1!"); };
template<Peripheral p> struct SignalConnection<DataB6::Fsb, p> {
	static_assert((p == Peripheral::Sai1),"GpioB6::Fsb only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataB6::Out, p> {
	static_assert((p == Peripheral::Comp4),"GpioB6::Out only connects to Comp4!"); };
template<Peripheral p> struct SignalConnection<DataB6::Tx, p> {
	static_assert((p == Peripheral::Usart1),"GpioB6::Tx only connects to Usart1!"); };
template<> struct SignalConnection<DataB6::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataB6::Bkin2, Peripheral::Tim8> { static constexpr int8_t af = 10; };
template<> struct SignalConnection<DataB6::Cc1, Peripheral::Ucpd1> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataB6::Ch1, Peripheral::Tim4> { static constexpr int8_t af = 2; };
template<> struct SignalConnection<DataB6::Ch1, Peripheral::Tim8> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataB6::Ch1n, Peripheral::Tim16> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataB6::Etr, Peripheral::Tim8> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataB6::Etr, Peripheral::Lptim1> { static constexpr int8_t af = 11; };
template<> struct SignalConnection<DataB6::Fsb, Peripheral::Sai1> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataB6::Out, Peripheral::Comp4> { static constexpr int8_t af = 8; };
template<> struct SignalConnection<DataB6::Tx, Peripheral::Usart1> { static constexpr int8_t af = 7; };

struct DataB7 {
	static constexpr Gpio::Port port = Gpio::Port::B;
	static constexpr uint8_t pin = 7;
	struct BitBang { using Data = DataB7; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Bkin { using Data = DataB7; static constexpr Gpio::Signal Signal = Gpio::Signal::Bkin; };
	struct Ch1n { using Data = DataB7; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1n; };
	struct Ch2 { using Data = DataB7; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2; };
	struct Ch4 { using Data = DataB7; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch4; };
	struct In2 { using Data = DataB7; static constexpr Gpio::Signal Signal = Gpio::Signal::In2; };
	struct Out { using Data = DataB7; static constexpr Gpio::Signal Signal = Gpio::Signal::Out; };
	struct Pvdin { using Data = DataB7; static constexpr Gpio::Signal Signal = Gpio::Signal::Pvdin; };
	struct Rx { using Data = DataB7; static constexpr Gpio::Signal Signal = Gpio::Signal::Rx; };
	struct Sda { using Data = DataB7; static constexpr Gpio::Signal Signal = Gpio::Signal::Sda; };
};
template<Peripheral p> struct SignalConnection<DataB7::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioB7::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataB7::Bkin, p> {
	static_assert((p == Peripheral::Tim8),"GpioB7::Bkin only connects to Tim8!"); };
template<Peripheral p> struct SignalConnection<DataB7::Ch1n, p> {
	static_assert((p == Peripheral::Tim17),"GpioB7::Ch1n only connects to Tim17!"); };
template<Peripheral p> struct SignalConnection<DataB7::Ch2, p> {
	static_assert((p == Peripheral::Tim4),"GpioB7::Ch2 only connects to Tim4!"); };
template<Peripheral p> struct SignalConnection<DataB7::Ch4, p> {
	static_assert((p == Peripheral::Tim3),"GpioB7::Ch4 only connects to Tim3!"); };
template<Peripheral p> struct SignalConnection<DataB7::In2, p> {
	static_assert((p == Peripheral::Lptim1),"GpioB7::In2 only connects to Lptim1!"); };
template<Peripheral p> struct SignalConnection<DataB7::Out, p> {
	static_assert((p == Peripheral::Comp3),"GpioB7::Out only connects to Comp3!"); };
template<Peripheral p> struct SignalConnection<DataB7::Pvdin, p> {
	static_assert((p == Peripheral::Sys),"GpioB7::Pvdin only connects to Sys!"); };
template<Peripheral p> struct SignalConnection<DataB7::Rx, p> {
	static_assert((p == Peripheral::Usart1),"GpioB7::Rx only connects to Usart1!"); };
template<Peripheral p> struct SignalConnection<DataB7::Sda, p> {
	static_assert((p == Peripheral::I2c1),"GpioB7::Sda only connects to I2c1!"); };
template<> struct SignalConnection<DataB7::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataB7::Bkin, Peripheral::Tim8> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataB7::Ch1n, Peripheral::Tim17> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataB7::Ch2, Peripheral::Tim4> { static constexpr int8_t af = 2; };
template<> struct SignalConnection<DataB7::Ch4, Peripheral::Tim3> { static constexpr int8_t af = 10; };
template<> struct SignalConnection<DataB7::In2, Peripheral::Lptim1> { static constexpr int8_t af = 11; };
template<> struct SignalConnection<DataB7::Out, Peripheral::Comp3> { static constexpr int8_t af = 8; };
template<> struct SignalConnection<DataB7::Pvdin, Peripheral::Sys> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataB7::Rx, Peripheral::Usart1> { static constexpr int8_t af = 7; };
template<> struct SignalConnection<DataB7::Sda, Peripheral::I2c1> { static constexpr int8_t af = 4; };

struct DataB8 {
	static constexpr Gpio::Port port = Gpio::Port::B;
	static constexpr uint8_t pin = 8;
	struct BitBang { using Data = DataB8; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Bkin { using Data = DataB8; static constexpr Gpio::Signal Signal = Gpio::Signal::Bkin; };
	struct Ch1 { using Data = DataB8; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch1; };
	struct Ch2 { using Data = DataB8; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch2; };
	struct Ch3 { using Data = DataB8; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch3; };
	struct Ck1 { using Data = DataB8; static constexpr Gpio::Signal Signal = Gpio::Signal::Ck1; };
	struct Mclka { using Data = DataB8; static constexpr Gpio::Signal Signal = Gpio::Signal::Mclka; };
	struct Out { using Data = DataB8; static constexpr Gpio::Signal Signal = Gpio::Signal::Out; };
	struct Rx { using Data = DataB8; static constexpr Gpio::Signal Signal = Gpio::Signal::Rx; };
	struct Scl { using Data = DataB8; static constexpr Gpio::Signal Signal = Gpio::Signal::Scl; };
};
template<Peripheral p> struct SignalConnection<DataB8::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioB8::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataB8::Bkin, p> {
	static_assert((p == Peripheral::Tim1),"GpioB8::Bkin only connects to Tim1!"); };
template<Peripheral p> struct SignalConnection<DataB8::Ch1, p> {
	static_assert((p == Peripheral::Tim16),"GpioB8::Ch1 only connects to Tim16!"); };
template<Peripheral p> struct SignalConnection<DataB8::Ch2, p> {
	static_assert((p == Peripheral::Tim8),"GpioB8::Ch2 only connects to Tim8!"); };
template<Peripheral p> struct SignalConnection<DataB8::Ch3, p> {
	static_assert((p == Peripheral::Tim4),"GpioB8::Ch3 only connects to Tim4!"); };
template<Peripheral p> struct SignalConnection<DataB8::Ck1, p> {
	static_assert((p == Peripheral::Sai1),"GpioB8::Ck1 only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataB8::Mclka, p> {
	static_assert((p == Peripheral::Sai1),"GpioB8::Mclka only connects to Sai1!"); };
template<Peripheral p> struct SignalConnection<DataB8::Out, p> {
	static_assert((p == Peripheral::Comp1),"GpioB8::Out only connects to Comp1!"); };
template<Peripheral p> struct SignalConnection<DataB8::Rx, p> {
	static_assert((p == Peripheral::Fdcan1),"GpioB8::Rx only connects to Fdcan1!"); };
template<Peripheral p> struct SignalConnection<DataB8::Scl, p> {
	static_assert((p == Peripheral::I2c1),"GpioB8::Scl only connects to I2c1!"); };
template<> struct SignalConnection<DataB8::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataB8::Bkin, Peripheral::Tim1> { static constexpr int8_t af = 12; };
template<> struct SignalConnection<DataB8::Ch1, Peripheral::Tim16> { static constexpr int8_t af = 1; };
template<> struct SignalConnection<DataB8::Ch2, Peripheral::Tim8> { static constexpr int8_t af = 10; };
template<> struct SignalConnection<DataB8::Ch3, Peripheral::Tim4> { static constexpr int8_t af = 2; };
template<> struct SignalConnection<DataB8::Ck1, Peripheral::Sai1> { static constexpr int8_t af = 3; };
template<> struct SignalConnection<DataB8::Mclka, Peripheral::Sai1> { static constexpr int8_t af = 14; };
template<> struct SignalConnection<DataB8::Out, Peripheral::Comp1> { static constexpr int8_t af = 8; };
template<> struct SignalConnection<DataB8::Rx, Peripheral::Fdcan1> { static constexpr int8_t af = 9; };
template<> struct SignalConnection<DataB8::Scl, Peripheral::I2c1> { static constexpr int8_t af = 4; };

struct DataF0 {
	static constexpr Gpio::Port port = Gpio::Port::F;
	static constexpr uint8_t pin = 0;
	struct BitBang { using Data = DataF0; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ch3n { using Data = DataF0; static constexpr Gpio::Signal Signal = Gpio::Signal::Ch3n; };
	struct In10 { using Data = DataF0; static constexpr Gpio::Signal Signal = Gpio::Signal::In10; };
	struct Nss { using Data = DataF0; static constexpr Gpio::Signal Signal = Gpio::Signal::Nss; };
	struct Oscin { using Data = DataF0; static constexpr Gpio::Signal Signal = Gpio::Signal::Oscin; };
	struct Sda { using Data = DataF0; static constexpr Gpio::Signal Signal = Gpio::Signal::Sda; };
	struct Ws { using Data = DataF0; static constexpr Gpio::Signal Signal = Gpio::Signal::Ws; };
};
template<Peripheral p> struct SignalConnection<DataF0::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioF0::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataF0::Ch3n, p> {
	static_assert((p == Peripheral::Tim1),"GpioF0::Ch3n only connects to Tim1!"); };
template<Peripheral p> struct SignalConnection<DataF0::In10, p> {
	static_assert((p == Peripheral::Adc1),"GpioF0::In10 only connects to Adc1!"); };
template<Peripheral p> struct SignalConnection<DataF0::Nss, p> {
	static_assert((p == Peripheral::Spi2),"GpioF0::Nss only connects to Spi2!"); };
template<Peripheral p> struct SignalConnection<DataF0::Oscin, p> {
	static_assert((p == Peripheral::Rcc),"GpioF0::Oscin only connects to Rcc!"); };
template<Peripheral p> struct SignalConnection<DataF0::Sda, p> {
	static_assert((p == Peripheral::I2c2),"GpioF0::Sda only connects to I2c2!"); };
template<Peripheral p> struct SignalConnection<DataF0::Ws, p> {
	static_assert((p == Peripheral::I2s2),"GpioF0::Ws only connects to I2s2!"); };
template<> struct SignalConnection<DataF0::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataF0::Ch3n, Peripheral::Tim1> { static constexpr int8_t af = 6; };
template<> struct SignalConnection<DataF0::In10, Peripheral::Adc1> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataF0::Nss, Peripheral::Spi2> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataF0::Oscin, Peripheral::Rcc> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataF0::Sda, Peripheral::I2c2> { static constexpr int8_t af = 4; };
template<> struct SignalConnection<DataF0::Ws, Peripheral::I2s2> { static constexpr int8_t af = 5; };
template<> constexpr int8_t AdcChannel<DataF0, Peripheral::Adc1> = 10;

struct DataF1 {
	static constexpr Gpio::Port port = Gpio::Port::F;
	static constexpr uint8_t pin = 1;
	struct BitBang { using Data = DataF1; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Ck { using Data = DataF1; static constexpr Gpio::Signal Signal = Gpio::Signal::Ck; };
	struct In10 { using Data = DataF1; static constexpr Gpio::Signal Signal = Gpio::Signal::In10; };
	struct Inm { using Data = DataF1; static constexpr Gpio::Signal Signal = Gpio::Signal::Inm; };
	struct Oscout { using Data = DataF1; static constexpr Gpio::Signal Signal = Gpio::Signal::Oscout; };
	struct Sck { using Data = DataF1; static constexpr Gpio::Signal Signal = Gpio::Signal::Sck; };
};
template<Peripheral p> struct SignalConnection<DataF1::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioF1::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataF1::Ck, p> {
	static_assert((p == Peripheral::I2s2),"GpioF1::Ck only connects to I2s2!"); };
template<Peripheral p> struct SignalConnection<DataF1::In10, p> {
	static_assert((p == Peripheral::Adc2),"GpioF1::In10 only connects to Adc2!"); };
template<Peripheral p> struct SignalConnection<DataF1::Inm, p> {
	static_assert((p == Peripheral::Comp3),"GpioF1::Inm only connects to Comp3!"); };
template<Peripheral p> struct SignalConnection<DataF1::Oscout, p> {
	static_assert((p == Peripheral::Rcc),"GpioF1::Oscout only connects to Rcc!"); };
template<Peripheral p> struct SignalConnection<DataF1::Sck, p> {
	static_assert((p == Peripheral::Spi2),"GpioF1::Sck only connects to Spi2!"); };
template<> struct SignalConnection<DataF1::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataF1::Ck, Peripheral::I2s2> { static constexpr int8_t af = 5; };
template<> struct SignalConnection<DataF1::In10, Peripheral::Adc2> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataF1::Inm, Peripheral::Comp3> { static constexpr int8_t af = -2; };
template<> struct SignalConnection<DataF1::Oscout, Peripheral::Rcc> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataF1::Sck, Peripheral::Spi2> { static constexpr int8_t af = 5; };
template<> constexpr int8_t AdcChannel<DataF1, Peripheral::Adc2> = 10;

struct DataG10 {
	static constexpr Gpio::Port port = Gpio::Port::G;
	static constexpr uint8_t pin = 10;
	struct BitBang { using Data = DataG10; static constexpr Gpio::Signal Signal = Gpio::Signal::BitBang; };
	struct Mco { using Data = DataG10; static constexpr Gpio::Signal Signal = Gpio::Signal::Mco; };
};
template<Peripheral p> struct SignalConnection<DataG10::BitBang, p> {
	static_assert(p == Peripheral::BitBang, "GpioG10::BitBang only connects to software drivers!"); };
template<Peripheral p> struct SignalConnection<DataG10::Mco, p> {
	static_assert((p == Peripheral::Rcc),"GpioG10::Mco only connects to Rcc!"); };
template<> struct SignalConnection<DataG10::BitBang, Peripheral::BitBang> { static constexpr int8_t af = -1; };
template<> struct SignalConnection<DataG10::Mco, Peripheral::Rcc> { static constexpr int8_t af = 0; };

} // namespace modm::platform::detail
/// @endcond