/*
 * Copyright (c) 2024, Niklas Hauser
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
// ----------------------------------------------------------------------------

#include <stdarg.h>
#include <stddef.h>
#include <modm/architecture/utils.hpp>

// ----------------------------------------------------------------------------
modm_weak modm_section(".printf_is_not_implemented!__Please_include_the__modm:printf__module_in_your_project!")
int vprintf(const char* format, va_list arg)
{
	(void) format;
	(void) arg;
	return 0;
}

modm_weak modm_section(".printf_is_not_implemented!__Please_include_the__modm:printf__module_in_your_project!")
int vsnprintf(char* s, size_t n, const char* format, va_list arg)
{
	(void) s;
	(void) n;
	(void) format;
	(void) arg;
	return 0;
}

modm_weak modm_section(".printf_is_not_implemented!__Please_include_the__modm:printf__module_in_your_project!")
int vsprintf(char* s, const char* format, va_list arg)
{
	(void) s;
	(void) format;
	(void) arg;
	return 0;
}

modm_weak modm_section(".printf_is_not_implemented!__Please_include_the__modm:printf__module_in_your_project!")
int vfctprintf(void (*out)(char c, void* extra_arg), void* extra_arg, const char* format, va_list arg)
{
	(void) out;
	(void) extra_arg;
	(void) format;
	(void) arg;
	return 0;
}

modm_weak modm_section(".printf_is_not_implemented!__Please_include_the__modm:printf__module_in_your_project!")
int printf(const char* format, ...)
{
	(void) format;
	return 0;
}

modm_weak modm_section(".printf_is_not_implemented!__Please_include_the__modm:printf__module_in_your_project!")
int sprintf(char* s, const char* format, ...)
{
	(void) s;
	(void) format;
	return 0;
}

modm_weak modm_section(".printf_is_not_implemented!__Please_include_the__modm:printf__module_in_your_project!")
int snprintf(char* s, size_t n, const char* format, ...)
{
	(void) s;
	(void) n;
	(void) format;
	return 0;
}

modm_weak modm_section(".printf_is_not_implemented!__Please_include_the__modm:printf__module_in_your_project!")
int fctprintf(void (*out)(char c, void* extra_arg), void* extra_arg, const char* format, ...)
{
	(void) out;
	(void) extra_arg;
	(void) format;
	return 0;
}