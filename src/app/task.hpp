#pragma once

#include "modm/processing/protothread.hpp"

template <typename T>
class Task: private T, public modm::pt::Protothread {
public:
    static inline void poll() {
        static Task<T> t;
        t.pollInternal();
    }

    Task(const Task &) = delete; 
    Task &operator=(const Task &) = delete; 

protected:
    Task() = default;
    ~Task() = default;

    bool pollInternal();
};

