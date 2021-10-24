#pragma once

#ifndef __RL_NUMBER_H__
#define __RL_NUMBER_H__

#include "rl_common.h"

namespace rl {

class num final
{
friend num           plus(const num& p_a, const num& p_b);

friend void          init_from_str(num&, const str_t&);
friend num           num_times_digit(const num&, const digit_t);

friend fundamental_t to_fundamental(const num&);
friend str_t         to_string(const num&);

friend void          print(const num&);

friend struct        DigitTable;

friend size_t        digit_count(const num&);
friend size_t        whole_part_size(const num&);
friend size_t        fraction_part_size(const num&);

friend bool          is_even(const num&);
friend bool          is_positive(const num&);
friend bool          is_negative(const num&);
friend bool          is_fraction(const num&);
friend bool          is_zero(const num&);

friend num           operator"" _rl(const char* p_str);

friend num           take_positive(const num&);
friend num           take_negative(const num&);

private:
    num() = default;

public:
    num(const str_t& p_num);
    num(const char* p_c_str);
    num(const vec_t<digit_t>& p_data, const size_t p_separator = 0, const bool p_sign = true);

    num pow(const num& p_power) const;
    num factorial() const;

    num operator+(const num& p_other) const;
    num operator-(const num& p_other) const;
    num operator*(const num& p_other) const;

    num& operator+=(const num& p_other);
    num& operator-=(const num& p_other);

    [[nodiscard]] bool operator>(const num& p_other) const;
    [[nodiscard]] bool operator<(const num& p_other) const;
    [[nodiscard]] bool operator==(const num& p_other) const;
    [[nodiscard]] bool operator!=(const num& p_other) const;

private:
    [[nodiscard]] bool      in_bounds(const int p_i) const;
    [[nodiscard]] digit_t&  operator[](const size_t p_i);
    [[nodiscard]] digit_t   operator[](const size_t p_i) const;
    [[nodiscard]] digit_t   get_or_0(const size_t p_i, const int p_shift = 0) const;

    void check_separator();
    void trim_left();
    void trim_right();
    void trim();

    bool sign{true};
    vec_t<digit_t> data;
    size_t separator{0};
};

[[nodiscard]] bool          is_even(const num&);
[[nodiscard]] bool          is_positive(const num&);
[[nodiscard]] bool          is_negative(const num&);
[[nodiscard]] bool          is_zero(const num&);
[[nodiscard]] bool          is_fraction(const num&);

[[nodiscard]] num           take_positive(const num&);
[[nodiscard]] num           take_negative(const num&);

[[nodiscard]] size_t        digit_count(const num&);
[[nodiscard]] size_t        whole_part_size(const num&);
[[nodiscard]] size_t        fraction_part_size(const num&);

[[nodiscard]] str_t         to_string(const num&);
[[nodiscard]] fundamental_t to_fundamental(const num&);

void print(const num&);

extern const num pi;
extern const num e;

}

::rl::num operator"" _l(const char* p_str);

#endif