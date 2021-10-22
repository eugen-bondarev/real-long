#include "rl_number.h"
#include "rl_common.h"

#include <sstream>

namespace rl {

static void init_from_str(Number& p_num, const str_t& p_str)
{
    p_num.data.reserve(p_str.size());

    for (size_t i = 0; i < p_str.size(); ++i)
    {
        if (p_str[i] == '.')
        {
            p_num.separator = i;
        }
        else if (p_str[i] == '-')
        {
            p_num.sign = false;
        }
        else
        {
            p_num.data.push_back(static_cast<digit_t>(p_str[i] - '0'));
        }
    }
}

Number::Number(const str_t& p_num)
{
    init_from_str((*this), p_num);
}

Number::Number(const char* p_c_str)
{
    init_from_str((*this), str_t(p_c_str));
}

Number::Number(const vec_t<digit_t>& p_data) : data{p_data}
{
}

size_t Number::digit_count() const
{
    return data.size();
}

size_t Number::whole_part_size() const
{
    return separator ? separator : digit_count();
}

size_t Number::fraction_part_size() const
{
    return digit_count() - whole_part_size();
}

str_t Number::to_string() const
{
    std::stringstream stream;
    for (size_t i = digit_count(); i-->0;)
    {
        stream << operator[](i);
        if ((digit_count() - i) == separator) stream << ".";
    }
    return stream.str();
}

void Number::print() const
{
    RL_LINE_OUT(to_string());
}

digit_t& Number::operator[](const size_t p_i)
{
    return data[digit_count() - 1 - p_i];
}

digit_t Number::operator[](const size_t p_i) const
{
    return data[digit_count() - 1 - p_i];
}

bool Number::in_bounds(const int p_i) const
{
    return p_i >= 0 && p_i < digit_count();
}

digit_t Number::get_or_0(const size_t p_i, const int p_shift) const
{
    const int final_i = static_cast<int>(p_i) + p_shift;
    return in_bounds(final_i) ? operator[](final_i) : 0;
}

Number Number::operator+(const Number& p_other) const
{
    const Number& a{(*this)};
    const Number& b{p_other};
    const size_t  largest_whole_part_size{std::max(a.whole_part_size(), b.whole_part_size())};
    const size_t  largest_fraction_part_size{std::max(a.fraction_part_size(), b.fraction_part_size())};
    const size_t  max_size{largest_whole_part_size + largest_fraction_part_size};

    Number c; c.data.reserve(max_size);

    size_t carry{0};
    for (size_t i = 0; i < max_size; ++i)
    {
        const int a_shift{static_cast<int>(a.fraction_part_size() - b.fraction_part_size())};
        const int b_shift{static_cast<int>(b.fraction_part_size() - a.fraction_part_size())};
        const digit_t a_digit{a.get_or_0(i, a_shift < 0 ? a_shift : 0)};
        const digit_t b_digit{b.get_or_0(i, b_shift < 0 ? b_shift : 0)};
        const digit_t c_digit{a_digit + b_digit + static_cast<digit_t>(carry)};
        digit_t c_final{c_digit};

        if (c_digit > 9)
        {
            carry = 1;
            c_final -= 10;
        }
        else
        {
            carry = 0;
        }
        c.data.push_back(c_final);
    }

    if (carry) c.data.push_back(1);

    if (largest_fraction_part_size)
    {
        c.separator = largest_whole_part_size;
    }

    std::reverse(std::begin(c.data), std::end(c.data));

    return c;
}

Number Number::operator-(const Number& p_other) const
{
    const Number& a{(*this)};
    const Number& b{p_other};
    const size_t  largest_whole_part_size{std::max(a.whole_part_size(), b.whole_part_size())};
    const size_t  largest_fraction_part_size{std::max(a.fraction_part_size(), b.fraction_part_size())};
    const size_t  max_size{largest_whole_part_size + largest_fraction_part_size};

    Number c; c.data.reserve(max_size);

    if (largest_fraction_part_size)
    {
        c.separator = largest_whole_part_size;
    }

    size_t carry{0};
    for (size_t i = 0; i < max_size; ++i)
    {
        const int a_shift{static_cast<int>(a.fraction_part_size() - b.fraction_part_size())};
        const int b_shift{static_cast<int>(b.fraction_part_size() - a.fraction_part_size())};
        const digit_t a_digit{a.get_or_0(i, a_shift < 0 ? a_shift : 0)};
        const digit_t b_digit{b.get_or_0(i, b_shift < 0 ? b_shift : 0)};
        const digit_t c_digit{static_cast<digit_t>(a_digit - b_digit - carry)};
        digit_t c_final{c_digit};
        
        RL_LINE_OUT(a_digit << " - " << b_digit << " = " << c_digit);

        if (c_digit < 0)
        {
            c_final += 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        
        c.data.push_back(c_final);
    }

    std::reverse(std::begin(c.data), std::end(c.data));

    return c;
}

Number& Number::operator+=(const Number& p_other)
{
    Number result = (*this) + p_other;
    (*this) = result;
    return (*this);
}

}