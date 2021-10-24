#pragma once

#ifndef __RL_NUMBER_H__
#define __RL_NUMBER_H__

#include "rl_common.h"

namespace rl {

class num final
{
friend void             init_from_str(num&, const str_t&);

friend fundamental_t    to_fundamental(const num&);
friend str_t            to_string(const num&);

friend void             print(const num&);

friend struct           DigitTable;

friend size_t           digit_count(const num&);
friend size_t           whole_part_size(const num&);
friend size_t           fraction_part_size(const num&);

friend bool             is_positive(const num&);
friend bool             is_negative(const num&);
friend bool             is_zero(const num&);

friend num              take_positive(const num&);
friend num              take_negative(const num&);

private:
    num() = default;

public:
    num(const str_t& p_num);
    num(const char* p_c_str);
    num(const vec_t<digit_t>& p_data);

    num operator+(const num& p_other) const;
    num operator-(const num& p_other) const;

    num& operator+=(const num& p_other);
    num& operator-=(const num& p_other);

    bool operator>(const num& p_other) const;
    bool operator<(const num& p_other) const;
    bool operator==(const num& p_other) const;

private:
    /**
     * Number a = "1234", a.in_bounds(0) = true, a.in_bounds(4) = false;
     */
    bool in_bounds(const int p_i) const;

    /**
     * Number a = "1234", a[0] = 4, a[1] = 3;
     */
    digit_t& operator[](const size_t p_i);
    digit_t operator[](const size_t p_i) const;

    /**
     * Number a = "28", a.get_or_0(0) = 8,      a.get_or_0(1) = 2,      a.get_or_0(2) = 0;
     * Number a = "28", a.get_or_0(0, 1) = 2,   a.get_or_0(0, 2) = 0;
     */
    digit_t get_or_0(const size_t p_i, const int p_shift = 0) const;

    void check_separator();
    void trim_left();
    void trim_right();
    void trim();

    bool sign{true};
    vec_t<digit_t> data;
    size_t separator{0};
};

size_t digit_count(const num&);
size_t whole_part_size(const num&);
size_t fraction_part_size(const num&);

str_t to_string(const num&);
fundamental_t to_fundamental(const num&);
void print(const num&);

extern const num pi;
extern const num e;

}

#endif