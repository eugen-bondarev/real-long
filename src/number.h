#pragma once

#ifndef __NUMBER_H__
#define __NUMBER_H__

#include <iostream>
#include <string>
#include <vector>

#define LOG_OUT(x) std::cout << x << std::endl
#define VAR_OUT(x) std::cout << #x << " = " << x << std::endl

using digit_t = short;
using fundamental_t = unsigned long long;

class Number
{
public:
    Number();
    Number(const std::vector<digit_t>& p_digits);
    Number(const size_t p_amount_of_digits);
    Number(const std::string& p_num);

    void append(const digit_t p_digit);

    Number multiply_by_digit(const digit_t p_digit) const;

    Number operator+(const Number& p_other) const;
    Number operator-(const Number& p_other) const;
    Number operator*(const Number& p_other) const;

    bool in_bounds(const size_t p_i) const;

    digit_t& operator[](const size_t p_i);
    digit_t operator[](const size_t p_i) const;

    digit_t& get_first();
    digit_t& get_last();    
    digit_t get_first() const;
    digit_t get_last() const;

    digit_t get_or(const size_t p_i, const digit_t p_or) const;

    size_t get_amount_of_digits() const;

    fundamental_t get_fundamental() const;

    void print_out() const;

private:
    std::vector<digit_t> data;
};

#endif