#pragma once

#include "modm/math.hpp"
#include "util/siso.hpp"

template <typename T>
struct limit_m {
    inline limit_m(const T min, const T max):
        min(min),
        max(max) {
    }
    inline limit_m(const T max): limit_m(-max, max) {}

    const T min;
    const T max;

    template <typename V>
    inline decltype(auto) operator()(V value) {
        if (value < min)
            value = min;
        if (value > max)
            value = max;
        return value;
    }
    template<uint8_t ROWS, uint8_t COLUMNS>
    inline void operator()(modm::Matrix<T, ROWS, COLUMNS> &m) {
        for (uint_fast8_t i = 0; i < ROWS * COLUMNS; ++i) {
            m.element[i] = operator()(m.element[i]);
        }
    }
    template<uint8_t N>
    inline void operator()(modm::Vector<T, N> &v) {
        operator()(v.asMatrix());
    }

};


