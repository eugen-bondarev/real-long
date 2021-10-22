#pragma once

#ifndef __RL_NUMBER_H__
#define __RL_NUMBER_H__

#include "rl_common.h"

namespace rl {

class Number final
{
friend void init_from_str(Number&, const str_t&);

private:
    Number() = default;

public:
    Number(const str_t& p_num);
    Number(const char* p_c_str);
    Number(const vec_t<digit_t>& p_data);

    /**
     * Number a = "1234", a.in_bounds(0) = true, a.in_bounds(4) = false;
     */
    bool in_bounds(const size_t p_i) const;

    /**
     * Number a = "1234", a[0] = 4, a[1] = 3;
     */
    digit_t& operator[](const size_t p_i);
    digit_t operator[](const size_t p_i) const;

    /**
     * Number a = "28", a.get_or_0(0) = 8,      a.get_or_0(1) = 2,      a.get_or_0(2) = 0;
     * Number a = "28", a.get_or_0(0, 1) = 2,   a.get_or_0(0, 2) = 0;
     */
    digit_t get_or_0(const size_t p_i, const size_t p_shift = 0) const;

    /**
     * Number a = "1234", digit_count() = 4
     */
    size_t digit_count() const;
    
    Number operator+(const Number& p_other) const;

    str_t to_string() const;
    void print() const;

private:
    vec_t<digit_t> data;
};

}

#endif