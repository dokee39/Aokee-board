#pragma once

#include <numbers>
#include <functional>
#include <type_traits>

/*siso defines*/
template <typename T>
concept Number = std::convertible_to<T, long double>;

template <typename SisoT, typename T>
concept Siso = requires(SisoT &siso, T input) {
    {input} -> std::convertible_to<long double>;
    {siso(input)} -> std::same_as<T>;
};

template <Number T>
using SisoFuncT = std::function<T (T)>;
using SisoFunc = SisoFuncT<float>;

template <typename Derived> 
class SisoSys {
public:
    inline auto operator()(auto input) {
        return static_cast<Derived *>(this)->calc(input);
    }
};


/*siso operators*/
template <Number T>
struct Out {
    explicit Out (T o): o(o) {}
    T o;

    operator T() {
        return o;
    }
    Out &operator>>(T &next) {
        next = o;
        return *this;
    }
};

template <Number T, Siso<T> Siso>
inline Out<T> operator>>(T input, Siso &&siso) {
    return Out<T>(siso(input));
}

template <Number T, Siso<T> Siso>
inline Out<T> operator>>(Out<T> input, Siso &&siso) {
    return Out<T>(siso(input));
}

template <Siso<float> Siso1, Siso<float> Siso2>
inline decltype(auto) operator>>(Siso1 &&siso1, Siso2 &&siso2) {
    return [&] (float input) -> float {
        return siso2(siso1(input));
    };
}

template <Number T, Siso<T> Siso>
inline T &operator<<(T &input, Siso &&siso) {
    input = siso(input);
    return input;
}

template <Number T, Siso<T> Siso>
inline decltype(auto) operator+(T &&x, Siso &&siso) {
    return [x = std::forward<T>(x),
            siso = std::forward<Siso>(siso)]
    (T input) -> T {
        return x + siso(input);
    };
};

template <Number T, Siso<T> Siso>
inline decltype(auto) operator+(Siso &&siso, T &&x) {
    return x + siso; 
};

template <Siso<float> Siso1, Siso<float> Siso2>
inline decltype(auto) operator+(Siso1 &&siso1, Siso2 &&siso2) {
    return [&] (float input) -> float {
        return siso1(input) + siso2(input);
    };
};


/*sisos*/
template <Number T>
inline constexpr auto limit(T min, T max) {
    return [=](T input) -> T {
        if (input < min)
            input = min;
        if (input > max)
            input = max;
        return input;
    };
};

inline constexpr auto limit(auto n) {
    return limit(-n, n);
};

template <Number T>
const auto rad_format {
    [](T input) -> T {
        static constexpr T &pi = std::numbers::pi_v<T>;
        if (input < -pi)
            input += 2 * pi;
        if (input >= pi)
            input -= 2 * pi;
        return input;
    }
};

struct PidParam {
    float kp;
    float ki;
    float kd;
    float max_iout;
    float max_out;
};

class Pid: public PidParam, public SisoSys<Pid> {
public:
    explicit Pid(const PidParam &param);
    explicit Pid(const std::array<float, 5> &param);
    explicit Pid(const float kp,
                 const float ki, 
                 const float kd,
                 const float max_iout,
                 const float max_out);
    float calc(float err);

private:
    float p_out {0.0f};
    float i_out {0.0f};
    float d_out {0.0f};
    float out {0.0f};
    float error[2] {0.0f};
};


inline Pid::Pid(const PidParam& param): 
    PidParam(param) {
}

inline Pid::Pid(const float kp,
                const float ki, 
                const float kd,
                const float max_iout,
                const float max_out):
    PidParam(kp, ki, kd, max_iout, max_out) {
}

inline float Pid::calc(float err) {
    error[1] = error[0];
    error[0] = err;
    p_out = kp * error[0];
    i_out += ki * error[0];
    d_out = kd * (error[0] - error[1]);
    i_out << limit(max_iout);
    out = p_out + i_out + d_out;
    out << limit(max_out);

    return out;
}


