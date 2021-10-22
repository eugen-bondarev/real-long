#pragma once

#ifndef __RL_NUMBER_H__
#define __RL_NUMBER_H__

#include "rl_common.h"

namespace rl {

class Number
{
public:
    Number() = default;
    Number(const str_t& p_num);
    Number(const vec_t<digit_t>& p_data);

    str_t to_string() const;
    void print() const;

    bool in_bounds(const size_t p_i) const;
    digit_t& operator[](const size_t p_i);
    digit_t operator[](const size_t p_i) const;
    digit_t get_or_0(const size_t p_i, const size_t p_shift = 0) const;

    Number operator+(const Number& p_other) const;

    size_t digit_count() const;

private:
    vec_t<digit_t> data;
};

}

#endif