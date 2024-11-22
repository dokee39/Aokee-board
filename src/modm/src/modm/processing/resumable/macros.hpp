/*
 * Copyright (c) 2014, Kevin Läufer
 * Copyright (c) 2014-2015, 2017-2018, Niklas Hauser
 * Copyright (c) 2017, Raphael Lehmann
 * Copyright (c) 2018, Fabian Greif
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#ifndef MODM_RF_MACROS_HPP
#define MODM_RF_MACROS_HPP

#include <modm/architecture/interface/assert.hpp>
#include <modm/architecture/utils.hpp>

/// @ingroup modm_processing_resumable
/// @{

#ifdef __DOXYGEN__
/// Declare start of resumable function with index.
/// @warning Use at start of the `resumable()` implementation!
#define RF_BEGIN(index)

/**
 * Declare start of a nested resumable function.
 * This will immediately return if the nesting is too deep.
 *
 * @warning Use at start of the `resumable()` implementation!
 */
#define RF_BEGIN()
#endif

/**
 * End the resumable function and return a result.
 *
 * @warning	Use at end of the `resumable()` implementation only!
 * @hideinitializer
 */
#define RF_END_RETURN(...) \
			RF_RETURN(__VA_ARGS__); \
			modm_fallthrough; \
		RF_INTERNAL_END()

/**
 * End the resumable function. You can use this to return `void`, or if the result does not matter.
 *
 * @warning	Use at end of the `resumable()` implementation only!
 * @hideinitializer
 */
#define RF_END() \
 			this->stopRf(rfIndex); \
			this->popRf(); \
			return {modm::rf::Stop}; \
		RF_INTERNAL_END()

/**
 * End the resumable function by calling another resumable function and returning its result.
 *
 * @warning	Use at end of the `resumable()` implementation only!
 * @hideinitializer
 */
#define RF_END_RETURN_CALL(...) \
			RF_RETURN_CALL(__VA_ARGS__); \
			modm_fallthrough; \
		RF_INTERNAL_END()

/// Yield resumable function until next invocation.
/// @hideinitializer
#define RF_YIELD() \
			RF_INTERNAL_SET_CASE_YIELD(__COUNTER__)

/// Cause resumable function to wait until given child protothread completes.
/// @hideinitializer
#define RF_WAIT_THREAD(...) 	RF_WAIT_UNTIL(!(__VA_ARGS__).run())

/// Cause resumable function to wait **while** given `condition` is true.
/// @hideinitializer
#define RF_WAIT_WHILE(...) \
		do { \
			RF_INTERNAL_SET_CASE(__COUNTER__); \
			if (__VA_ARGS__) { \
				this->popRf(); \
				return {modm::rf::Running}; \
			} \
		} while(0)

/// Cause resumable function to wait **until** given `condition` is true.
/// @hideinitializer
#define RF_WAIT_UNTIL(...) \
	RF_WAIT_WHILE(!(__VA_ARGS__))

/// Calls a resumable function and returns its result.
/// @hideinitializer
#define RF_CALL(...) \
	({ \
			RF_INTERNAL_SET_CASE(__COUNTER__); \
			auto rfResult = (__VA_ARGS__); \
			if (rfResult.getState() > modm::rf::NestingError) { \
				this->popRf(); \
				return {modm::rf::Running}; \
			} \
			rfResult.getResult(); \
	})

/**
 * Calls a resumable function, busy-waits and returns its result.
 *
 * @warning	Use this with extreme caution, this can cause deadlocks!
 * @hideinitializer
 */
#define RF_CALL_BLOCKING(...) \
	({ \
			decltype(__VA_ARGS__) rfResult{0}; \
			do { rfResult = (__VA_ARGS__); } \
			while (rfResult.getState() > modm::rf::NestingError); \
			rfResult.getResult(); \
	})

/// Exits a resumable function and returns another resumable function's result.
/// @hideinitializer
#define RF_RETURN_CALL(...) \
		do { \
			RF_INTERNAL_SET_CASE(__COUNTER__); \
			{ \
				auto rfResult = (__VA_ARGS__); \
				if (rfResult.getState() > modm::rf::NestingError) { \
					this->popRf(); \
					return {modm::rf::Running}; \
				} \
				RF_RETURN(rfResult.getResult()); \
			} \
		} while(0)

#ifdef __DOXYGEN__
/// Stop and exit from resumable function with a result.
/// @hideinitializer
#define RF_RETURN(result)

/// Stop and exit from resumable function of `void` return type.
/// @hideinitializer
#define RF_RETURN()
#endif

/// @}

#ifndef __DOXYGEN__
// Required macro to set the same unique number twice
#define RF_INTERNAL_SET_CASE(counter) \
			this->setRf((counter % 255) + 1, rfIndex); \
			modm_fallthrough; \
		case ((counter % 255) + 1): ;

// Internal macro for yield
#define RF_INTERNAL_SET_CASE_YIELD(counter) \
			this->setRf((counter % 255) + 1, rfIndex); \
			this->popRf(); \
			return {modm::rf::Running}; \
		case ((counter % 255) + 1): ;

#define RF_INTERNAL_END() \
		default: \
			this->popRf(); \
			return {modm::rf::WrongState}; \
	} \
	static_assert(uint16_t(__COUNTER__) - rfCounter < 256, "You have too many states in this resumable function!")

#define RF_RETURN_0() \
	do { \
			this->stopRf(rfIndex); \
			this->popRf(); \
			return {modm::rf::Stop}; \
	} while(0)

#define RF_RETURN_1(result) \
	do { \
			this->stopRf(rfIndex); \
			this->popRf(); \
			return {modm::rf::Stop, (result)}; \
	} while(0)

// Beginner structure for nested resumable functions
#define RF_BEGIN_0() \
	constexpr uint16_t rfCounter = __COUNTER__; \
	this->template checkRfType<true>(); \
	constexpr uint8_t rfIndex = 0; \
	if (not this->nestingOkRf()) { \
		return {modm::rf::NestingError}; \
	} \
	switch (this->pushRf(0)) { \
		case (::modm::rf::Stopped): \
			RF_INTERNAL_SET_CASE(__COUNTER__);

// Beginner structure for conventional resumable functions
#define RF_BEGIN_1(index) \
	constexpr uint16_t rfCounter = __COUNTER__; \
	this->template checkRfFunctions<index>(); \
	this->template checkRfType<false>(); \
	constexpr uint_fast8_t rfIndex = index; \
	switch (this->pushRf(index)) { \
		case (::modm::rf::Stopped): \
			RF_INTERNAL_SET_CASE(__COUNTER__);

#define MODM_RF_GET_MACRO(_0, _1, NAME, ...) NAME
#define RF_BEGIN(...) MODM_RF_GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, RF_BEGIN_1, RF_BEGIN_0)(__VA_ARGS__)
#define RF_RETURN(...) MODM_RF_GET_MACRO(_0 __VA_OPT__(,) __VA_ARGS__, RF_RETURN_1, RF_RETURN_0)(__VA_ARGS__)

#endif

#endif // MODM_RF_MACROS_HPP
