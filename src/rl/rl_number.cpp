#include "rl_number.h"
#include "rl_common.h"

#include <sstream>

namespace rl {

Number::Number(const str_t& p_num)
{
    data.reserve(p_num.size());

    for (size_t i = 0; i < p_num.size(); ++i)
    {
        data.push_back(static_cast<digit_t>(p_num[i] - '0'));
    }
}

Number::Number(const vec_t<digit_t>& p_data) : data{p_data}
{
}

size_t Number::digit_count() const
{
    return data.size();
}

str_t Number::to_string() const
{
    std::stringstream stream;
    for (size_t i = digit_count(); i-->0;)
    {
        stream << operator[](i);
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

bool Number::in_bounds(const size_t p_i) const
{
    return p_i < digit_count();
}

digit_t Number::get_or_0(const size_t p_i, const size_t p_shift) const
{
    const size_t final_i = p_i + p_shift;
    return in_bounds(final_i) ? operator[](final_i) : 0;
}

Number Number::operator+(const Number& p_other) const
{
    const Number& a{(*this)};
    const Number& b{p_other};
    const size_t  max_size{std::max(a.digit_count(), b.digit_count())};

    Number c; c.data.reserve(max_size);

    size_t carry{0};
    for (size_t i = 0; i < max_size; i++)
    {
        const digit_t a_digit{a.get_or_0(i)};
        const digit_t b_digit{b.get_or_0(i)};
        const digit_t c_digit{a_digit + b_digit + static_cast<digit_t>(carry)};
        digit_t c_final{c_digit};

        if (c_digit > 9)
        {
            c_final -= 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        c.data.push_back(c_final);
    }

    if (carry) c.data.push_back(1);

    std::reverse(std::begin(c.data), std::end(c.data));

    return c;
}

}