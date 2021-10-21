#include "number.h"

#include <iostream>

Number::Number()
{
}

Number::Number(const std::vector<digit_t>& p_digits) : data{p_digits}
{

}

Number::Number(const size_t p_amount_of_digits)
{
    data.resize(p_amount_of_digits);
}

Number::Number(const std::string& p_num)
{
    data.resize(p_num.size());
    for (size_t i = 0; i < p_num.size(); i++)
    {
        data[i] = static_cast<digit_t>(p_num[i] - '0');
    }
}

void Number::append(const digit_t p_digit)
{
    data.push_back(p_digit);
}

bool Number::in_bounds(const size_t p_i) const
{
    return p_i < data.size();
}

digit_t& Number::operator[](const size_t p_i)
{
    return data[get_amount_of_digits() - p_i - 1];
}

digit_t Number::operator[](const size_t p_i) const
{
    return data[get_amount_of_digits() - p_i - 1];
}

digit_t& Number::get_first()
{
    return operator[](0);
}

digit_t Number::get_first() const
{
    return operator[](0);
}

digit_t& Number::get_last()
{
    return operator[](get_amount_of_digits() - 1);
}

digit_t Number::get_last() const
{
    return operator[](get_amount_of_digits() - 1);
}

digit_t Number::get_or(const size_t p_i, const digit_t p_or) const
{
    return in_bounds(p_i) ? operator[](p_i) : p_or;
}

Number Number::operator+(const Number& p_other) const
{
    const Number& a = (*this);
    const Number& b = p_other;
    const size_t  max_digits{std::max(a.get_amount_of_digits(), b.get_amount_of_digits())};
    Number c;
    c.data.reserve(max_digits);

    digit_t mark{0};
    for (size_t i = 0; i < max_digits; i++)
    {
        const digit_t a_digit{a.get_or(i, 0)};
        const digit_t b_digit{b.get_or(i, 0)};
        digit_t result_digit{static_cast<digit_t>(a_digit + b_digit + mark)};
        
        if (result_digit > 9)
        {
            mark = 1;
            result_digit -= 10;
        }
        else
        {
            mark = 0;
        }
        c.data.push_back(result_digit);
    }
    if (mark) c.data.push_back(1);

    std::reverse(std::begin(c.data), std::end(c.data));

    return c;
}

Number Number::operator-(const Number& p_other) const
{
    const Number& a = (*this);
    const Number& b = p_other;
    const size_t  max_digits{std::max(a.get_amount_of_digits(), b.get_amount_of_digits())};
    Number c;
    c.data.reserve(max_digits);

    int borrowed_from{-1};
    for (size_t i = 0; i < max_digits; i++)
    {
        const digit_t a_digit{borrowed_from != i ? a.get_or(i, 0) : static_cast<digit_t>(a.get_or(i, 0) - 1)};
        const digit_t b_digit{b.get_or(i, 0)};
        const bool a_is_less{a_digit < b_digit};

        if (a_is_less) { borrowed_from = i + 1; }
        digit_t result_digit{static_cast<digit_t>(a_digit - b_digit + (a_is_less * 10))};
        
        if (!(c.data.size() && i == max_digits - 1 && result_digit == 0))
        {
            c.data.push_back(result_digit);
        }
    }

    std::reverse(std::begin(c.data), std::end(c.data));

    return c;
}

Number Number::multiply_by_digit(const digit_t p_digit) const
{
    Number result({ 0 });

    for (size_t i = 0; i < static_cast<size_t>(p_digit); i++)
    {
        result = result + (*this);
    }

    return result;
}

Number Number::operator*(const Number& p_other) const
{
    const Number& a = get_amount_of_digits() >= p_other.get_amount_of_digits() ? (*this) : p_other;
    const Number& b = get_amount_of_digits() >= p_other.get_amount_of_digits() ? p_other : (*this);
    const size_t  max_digits{std::max(a.get_amount_of_digits(), b.get_amount_of_digits())};
    Number c;
    c.data.reserve(max_digits);

    std::vector<Number> to_add(b.get_amount_of_digits());
    for (size_t i = 0; i < b.get_amount_of_digits(); i++)
    {
        to_add[i] = a.multiply_by_digit(b[i]);

        for (size_t j = 0; j < i; j++)
        {
            to_add[i].append(0);
        }
    }

    for (size_t i = 0; i < to_add.size(); i++)
    {
        c = c + to_add[i];
    }

    return c;
}

size_t Number::get_amount_of_digits() const
{
    return data.size();
}

fundamental_t Number::get_fundamental() const
{
    fundamental_t num{0};
    for (size_t i = 0; i < get_amount_of_digits(); i++)
    {
        num += pow(10, i) * operator[](i);
    }
    return num;
}

void Number::print_out() const
{
    for (size_t i = 0; i < data.size(); i++)
    {
        std::cout << data[i];
    }
    std::cout << std::endl;
}