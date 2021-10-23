#include "rl_number.h"
#include "rl_common.h"

#include <sstream>
#include <algorithm>

namespace rl {

static void init_from_str(Number& p_num, const str_t& p_str)
{
    p_num.data.reserve(p_str.size());

    for (size_t i = 0; i < p_str.size(); ++i)
    {
        if (p_str[i] == '.')
        {
            p_num.separator = i - !p_num.sign;
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
    if (!sign)
    {
        stream << "-";
    }
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
        c.separator = largest_whole_part_size + carry;
    }

    std::reverse(std::begin(c.data), std::end(c.data));

    c.check_separator();

    return c;
}

void Number::trim_left()
{
    bool only_zeros{true};
    for (size_t i = 0; i < whole_part_size(); i++)
    {
        if (data[i] != 0)
        {
            only_zeros = false;
        }
    }

    if (only_zeros)
    {
        data.erase(std::begin(data) + whole_part_size() - 1);
        if (digit_count() == 0)
        {
            data = {0};
        }
        return;
    }

    size_t last_fraction_size{fraction_part_size()};
    size_t first_non_zero{0};
    for (size_t i = 0; i < whole_part_size(); i++)
    {
        if (data[i] != 0)
        {
            first_non_zero = i;
            break;
        }
    }

    data.erase(std::begin(data), std::begin(data) + first_non_zero);
    separator = digit_count() - last_fraction_size;
}

void Number::trim_right()
{
}

void Number::trim()
{
    trim_left();
    // trim_right();
}

Number Number::operator-(const Number& p_other) const
{
    const Number& greater{(*this) > p_other ? (*this) : p_other};
    const Number& less{(*this) < p_other ? (*this) : p_other};

    const Number& a{greater};
    const Number& b{less};
    const bool    this_is_less{this == &b};
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

    if (this_is_less)
    {
        c.sign = false;
    }

    std::reverse(std::begin(c.data), std::end(c.data));

    c.trim();
    c.check_separator();

    return c;
}

Number& Number::operator+=(const Number& p_other)
{
    Number result = (*this) + p_other;
    (*this) = result;
    return (*this);
}

Number& Number::operator-=(const Number& p_other)
{
    Number result = (*this) - p_other;
    (*this) = result;
    return (*this);
}

void Number::check_separator()
{
    if (separator == digit_count())
    {
        separator = 0;
    }
}

bool Number::operator>(const Number& p_other) const
{
    if (whole_part_size() > p_other.whole_part_size())
    {
        return true;
    }

    if (p_other.whole_part_size() > whole_part_size())
    {
        return false;
    }

    const Number& a{(*this)};
    const Number& b{p_other};

    const size_t  largest_whole_part_size{std::max(a.whole_part_size(), b.whole_part_size())};
    const size_t  largest_fraction_part_size{std::max(a.fraction_part_size(), b.fraction_part_size())};
    const size_t  max_size{largest_whole_part_size + largest_fraction_part_size};
    
    for (size_t i = max_size; i-->0;)
    {
        const int a_shift{static_cast<int>(a.fraction_part_size() - b.fraction_part_size())};
        const int b_shift{static_cast<int>(b.fraction_part_size() - a.fraction_part_size())};
        const digit_t a_digit{a.get_or_0(i, a_shift < 0 ? a_shift : 0)};
        const digit_t b_digit{b.get_or_0(i, b_shift < 0 ? b_shift : 0)};

        if (a_digit > b_digit)
        {
            return true;
        }
        if (a_digit < b_digit)
        {
            return false;
        }
    }

    return false;
}

bool Number::operator<(const Number& p_other) const
{
    if (whole_part_size() > p_other.whole_part_size())
    {
        return false;
    }

    if (p_other.whole_part_size() > whole_part_size())
    {
        return true;
    }

    const Number& a{(*this)};
    const Number& b{p_other};

    const size_t  largest_whole_part_size{std::max(a.whole_part_size(), b.whole_part_size())};
    const size_t  largest_fraction_part_size{std::max(a.fraction_part_size(), b.fraction_part_size())};
    const size_t  max_size{largest_whole_part_size + largest_fraction_part_size};
    
    for (size_t i = max_size; i-->0;)
    {
        const int a_shift{static_cast<int>(a.fraction_part_size() - b.fraction_part_size())};
        const int b_shift{static_cast<int>(b.fraction_part_size() - a.fraction_part_size())};
        const digit_t a_digit{a.get_or_0(i, a_shift < 0 ? a_shift : 0)};
        const digit_t b_digit{b.get_or_0(i, b_shift < 0 ? b_shift : 0)};

        if (a_digit > b_digit)
        {
            return false;
        }
        if (a_digit < b_digit)
        {
            return true;
        }
    }

    return false;
}

fundamental_f_t Number::get_fundamental() const
{
    fundamental_f_t result{0};
    for (size_t i = 0; i < digit_count(); ++i)
    {
        result += operator[](i) * pow(10, i);
    }
    result /= pow(10, (digit_count() - separator));
    result *= static_cast<int>(sign) * 2 - 1;
    return result;
}

}