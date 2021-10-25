#include "rl_number.h"
#include "rl_common.h"

#include <sstream>
#include <algorithm>

namespace rl {

const num pi = num("3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481117450284102701938521105559644622948954930381964428810975665933446128475648233786783165271201909145648566923460348610454326648213393607260249141273724587006606315588174881520920962829254091715364367892590360011330530548820466521384146951941511609433057270365759591953092186117381932611793105118548074462379962749567351885752724891227938183011949129833673362440656643086021394946395224737190702179860943702770539217176293176752384674818467669405132000568127145263560827785771342757789609173637178721468440901224953430146549585371050792279689258923542019956112129");
const num e = num("2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427427466391932003059921817413596629043572900334295260595630738132328627943490763233829880753195251019011573834187930702154089149934884167509244761460668082264800168477411853742345442437107539077744992069551702761838606261331384583000752044933826560297606737113200709328709127443747047230696977209310141692836819025515108657463772111252389784425056953696770785449969967946864454905987931636889230098793127736178215424999229576351482208269895193668033182528869398496465105820939239829488793320362509443117301238197068416140397019837679320683282376464804295311802328782509819455815301756717361332069811250996181881593041690");

static void init_from_str(num& p_num, const str_t& p_str)
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

num::num(const str_t& p_num)
{
    init_from_str((*this), p_num);
}

num::num(const char* p_c_str)
{
    init_from_str((*this), str_t(p_c_str));
}

num::num(const vec_t<digit_t>& p_data, const size_t p_separator, const bool p_sign) : data{p_data}, separator{p_separator}, sign{p_sign}
{
}

size_t digit_count(const num& p_num)
{
    return p_num.data.size();
}

size_t whole_part_size(const num& p_num)
{
    return p_num.separator ? p_num.separator : digit_count(p_num);
}

size_t fraction_part_size(const num& p_num)
{
    return digit_count(p_num) - whole_part_size(p_num);
}

str_t to_string(const num& p_num)
{
    std::stringstream stream;
    if (!p_num.sign)
    {
        stream << "-";
    }
    for (size_t i = digit_count(p_num); i-->0;)
    {
        stream << p_num[i];
        if ((digit_count(p_num) - i) == p_num.separator) stream << ".";
    }
    return stream.str();
}

void print(const num& p_num)
{
    RL_LINE_OUT(to_string(p_num));
}

digit_t& num::operator[](const size_t p_i)
{
    return data[digit_count((*this)) - 1 - p_i];
}

digit_t num::operator[](const size_t p_i) const
{
    return data[digit_count((*this)) - 1 - p_i];
}

bool num::in_bounds(const int p_i) const
{
    return p_i >= 0 && p_i < digit_count((*this));
}

digit_t num::get_or_0(const size_t p_i, const int p_shift) const
{
    const int final_i = static_cast<int>(p_i) + p_shift;
    return in_bounds(final_i) ? operator[](final_i) : 0;
}

bool is_even(const num& p_num)
{
    return p_num[0] % 2 == 0;
}

bool is_positive(const num& p_num)
{
    return !is_zero(p_num) && p_num.sign;
}

bool is_negative(const num& p_num)
{
    return !is_zero(p_num) && !p_num.sign;
}

bool is_fraction(const num& p_num)
{
    return p_num.separator != 0;
}

bool is_zero(const num& p_num)
{
    return p_num == num(0_l);
}

num take_positive(const num& p_num)
{
    if (is_positive(p_num)) { return p_num; }

    num result = p_num; result.sign = true;
    return result;
}

num take_negative(const num& p_num)
{
    if (is_negative(p_num)) { return p_num; }

    num result = p_num; result.sign = false;
    return result;
}

num& num::trim_left()
{
    if (data[0] != 0) return (*this);

    size_t last_fraction_size{fraction_part_size((*this))};
    size_t first_non_zero{whole_part_size((*this)) - 1};
    for (size_t i = 0; i < whole_part_size((*this)); i++)
    {
        if (data[i] != 0)
        {
            first_non_zero = i;
            break;
        }
    }

    if (first_non_zero != 0)
    {
        data.erase(std::begin(data), std::begin(data) + first_non_zero);
    }
    else
    {
        data.erase(std::begin(data), std::begin(data) + whole_part_size((*this)) - 1);
    }

    separator = digit_count((*this)) - last_fraction_size;

    return (*this);
}

num& num::trim_right()
{
    if (data[data.size() - 1] != 0) return (*this);

    size_t first_non_zero{0};

    for (size_t i = digit_count((*this)); i-->digit_count((*this)) - fraction_part_size((*this));)
    {
        if (data[i] != 0)
        {
            first_non_zero = i;
            break;
        }
    }

    if (first_non_zero != 0)
    {
        data.erase(std::begin(data) + first_non_zero + 1, std::end(data));
    }
    else
    {
        data.erase(std::begin(data) + digit_count((*this)) - fraction_part_size((*this)), std::end(data));
    }

    return (*this);
}

num& num::trim()
{
    return trim_left().trim_right();
}

struct DigitTable
{
    digit_t a;
    digit_t b;

    DigitTable(const num& p_a, const num& p_b, const size_t p_i)
    {
        const int a_shift{static_cast<int>(fraction_part_size(p_a) - fraction_part_size(p_b))};
        const int b_shift{static_cast<int>(fraction_part_size(p_b) - fraction_part_size(p_a))};
        a = p_a.get_or_0(p_i, a_shift < 0 ? a_shift : 0);
        b = p_b.get_or_0(p_i, b_shift < 0 ? b_shift : 0);
    }
};

static num plus(const num& p_a, const num& p_b)
{
    if (is_negative(p_a) && is_positive(p_b))
    {
        return p_b - take_positive(p_a);
    }

    if (is_negative(p_a) && is_negative(p_b))
    {
        return take_negative(take_positive(p_a) + take_positive(p_b));
    }

    if (is_negative(p_b))
    {
        return p_a - take_positive(p_b);
    }

    const num& a{p_a};
    const num& b{p_b};
    const size_t  largest_whole_part_size{std::max(whole_part_size(a), whole_part_size(b))};
    const size_t  largest_fraction_part_size{std::max(fraction_part_size(a), fraction_part_size(b))};
    const size_t  max_size{largest_whole_part_size + largest_fraction_part_size};

    num c; c.data.reserve(max_size);

    size_t carry{0};
    for (size_t i = 0; i < max_size; ++i)
    {
        DigitTable digit(a, b, i);
        const digit_t c_digit{digit.a + digit.b + static_cast<digit_t>(carry)};
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

    return c;
}

num num::operator+(const num& p_other) const
{
    num c = plus((*this), p_other);

    c.trim();
    c.check_separator();

    return c;
}

num num::operator-(const num& p_other) const
{
    if (is_negative((*this)) && is_positive(p_other))
    {
        return take_negative(take_positive((*this)) + take_positive(p_other));
    }

    if (is_negative(p_other))
    {
        return (*this) + take_positive(p_other);
    }

    const num& greater{(*this) > p_other ? (*this) : p_other};
    const num& less{(*this) < p_other ? (*this) : p_other};

    const num& a{greater};
    const num& b{less};
    const bool    this_is_less{this == &b};
    const size_t  largest_whole_part_size{std::max(whole_part_size(a), whole_part_size(b))};
    const size_t  largest_fraction_part_size{std::max(fraction_part_size(a), fraction_part_size(b))};
    const size_t  max_size{largest_whole_part_size + largest_fraction_part_size};

    num c; c.data.reserve(max_size);

    if (largest_fraction_part_size)
    {
        c.separator = largest_whole_part_size;
    }

    size_t carry{0};
    for (size_t i = 0; i < max_size; ++i)
    {
        DigitTable digit(a, b, i);
        const digit_t c_digit{static_cast<digit_t>(digit.a - digit.b - carry)};
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

static void split_number(std::vector<digit_t>& p_digits, digit_t p_number) 
{
    if (p_number == 0) 
    { 
        p_digits.push_back(0);
    } 
    else 
    {
        while (p_number != 0) 
        {
            const digit_t last = p_number % 10;
            p_digits.push_back(last);
            p_number = (p_number - last) / 10;
        }
    }
}

static num num_times_digit(const num& p_a, const digit_t p_b)
{
    const num&   a{p_a};
    const size_t max_size{digit_count(a)};
    num c; c.data.reserve(max_size);

    size_t carry{0};
    for (size_t i = 0; i < max_size; ++i)
    {
        const digit_t c_digit{static_cast<digit_t>(p_a[i] * p_b + carry)};
        digit_t c_final{c_digit};

        if (c_digit > 9)
        {
            carry = (c_final - (c_final % 10)) / 10;
            c_final -= carry * 10;
        }
        else
        {
            carry = 0;
        }
        c.data.push_back(c_final);
    }
    if (carry)
    {
        split_number(c.data, carry);
    }

    std::reverse(std::begin(c.data), std::end(c.data));

    return c;
}

num num::operator*(const num& p_other) const
{
    if (is_zero((*this)) || is_zero(p_other))
    {
        return 0_l;
    }

    vec_t<num> results; results.reserve(digit_count(p_other));
    for (size_t i = 0; i < digit_count(p_other); ++i)
    {
        num result = num_times_digit((*this), p_other[i]);

        for (size_t j = 0; j < i; ++j)
        {
            result.data.push_back(0);
        }

        results.push_back(result);
    }

    num c = 0_l;
    for (size_t i = 0; i < results.size(); ++i)
    {
        c = plus(c, results[i]);
    }

    c.separator = digit_count(c) - (fraction_part_size((*this)) + fraction_part_size(p_other));
    c.trim();
    c.check_separator();

    c.sign = !((!sign) ^ (!p_other.sign));

    return c;
}

struct DivisionResult
{
    num quotient;
    num remainder;
};

static DivisionResult division_with_remainder(const num& p_dividend, const num& p_divisor)
{
    DivisionResult result { 0_l, p_dividend };

    while (result.remainder >= p_divisor)
    {
        result.remainder -= p_divisor;
        result.quotient = result.quotient + 1_l;
    }

    return result;
}

template <typename T>
static bool vector_contains(const vec_t<T>& p_vec, const T& p_el)
{
    for (size_t i = 0; i < p_vec.size(); i++)
    {
        if (p_vec[i] == p_el)
        {
            return true;
        }
    }
    return false;
}

num num::operator/(const num& p_other) const
{
    num dividend{take_positive((*this))};
    num divisor{take_positive(p_other)};

    if (is_zero(divisor))
    {
        throw std::runtime_error("Illigal division by 0.");
    }

    if (is_zero(dividend))
    {
        return 0_l;
    }

    if (dividend.trim().check_separator() != num(1_l))
    {
        num quotient = dividend * (1_l / divisor);
        quotient.sign = !((!sign) ^ (!p_other.sign));
        return quotient;
    }

    num quotient;

    const size_t divisor_fraction_size{fraction_part_size(divisor)};
    divisor.separator = 0;
    divisor.trim_left();

    size_t zeros{0};
    while (dividend < divisor)
    {
        dividend.data.push_back(0);
        zeros += 1;
    }

    if (zeros > 0)
    {
        quotient.separator = 1;
    }

    for (size_t i = 0; i < zeros; ++i)
    {
        quotient.data.push_back(0);
    }

    DivisionResult division = division_with_remainder(dividend, divisor);
    division.remainder.separator = 0;

    vec_t<num> remainders;
    while (division.remainder != 0_l && remainders.size() < 1000)
    {
        quotient.data.push_back(division.quotient.data[0]);

        bool first_iteration{true};
        while (division.remainder < divisor)
        {
            division.remainder.data.push_back(0);

            // If we still can't divide.
            if (!first_iteration)
            {
                quotient.data.push_back(0);
            }
            first_iteration = false;
        }
        
        division = division_with_remainder(division.remainder, divisor);
        division.remainder.separator = 0;
        remainders.push_back(division.remainder);
    }
    quotient.data.push_back(division.quotient.data[0]);

    if (divisor_fraction_size != 0)
    {
        quotient *= (10_l).pow(std::to_string(divisor_fraction_size));
    }

    quotient.sign = !((!sign) ^ (!p_other.sign));

    return quotient.trim().check_separator();
}

num num::pow(const num& p_power) const
{
    num c = (*this);
    for (num i = 0_l; i < p_power - 1_l; i++)
    {
        c = c * (*this);
    }
    return c;
}

num num::factorial() const
{
    num c = (*this);
    for (num i = (*this) - 1_l; i > 0_l; i--)
    {
        c = c * i;
    }
    return c;
}

num& num::operator+=(const num& p_other)
{
    const num result = (*this) + p_other;
    (*this) = result;
    return (*this);
}

num& num::operator-=(const num& p_other)
{
    const num result = (*this) - p_other;
    (*this) = result;
    return (*this);
}

num& num::operator*=(const num& p_other)
{
    const num result = (*this) * p_other;
    (*this) = result;
    return (*this);
}

num num::operator++(int)
{
    const num result = (*this) + 1_l;
    (*this) = result;
    return (*this);
}

num num::operator--(int)
{
    const num result = (*this) - 1_l;
    (*this) = result;
    return (*this);
}

num& num::check_separator()
{
    if (separator == digit_count((*this)))
    {
        separator = 0;
    }

    return (*this);
}

bool num::operator>(const num& p_other) const
{
    if (whole_part_size((*this)) > whole_part_size(p_other))
    {
        return true;
    }

    if (whole_part_size(p_other) > whole_part_size((*this)))
    {
        return false;
    }

    const num& a{(*this)};
    const num& b{p_other};

    const size_t  largest_whole_part_size{std::max(whole_part_size(a), whole_part_size(b))};
    const size_t  largest_fraction_part_size{std::max(fraction_part_size(a), fraction_part_size(b))};
    const size_t  max_size{largest_whole_part_size + largest_fraction_part_size};
    
    for (size_t i = max_size; i-->0;)
    {
        const int a_shift{static_cast<int>(fraction_part_size(a) - fraction_part_size(b))};
        const int b_shift{static_cast<int>(fraction_part_size(b) - fraction_part_size(a))};
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

bool num::operator>=(const num& p_other) const
{
    return !(operator<(p_other));
}

bool num::operator<=(const num& p_other) const
{
    return !(operator>(p_other));
}

bool num::operator<(const num& p_other) const
{
    if (whole_part_size((*this)) > whole_part_size(p_other))
    {
        return false;
    }

    if (whole_part_size(p_other) > whole_part_size((*this)))
    {
        return true;
    }

    const num& a{(*this)};
    const num& b{p_other};

    const size_t  largest_whole_part_size{std::max(whole_part_size(a), whole_part_size(b))};
    const size_t  largest_fraction_part_size{std::max(fraction_part_size(a), fraction_part_size(b))};
    const size_t  max_size{largest_whole_part_size + largest_fraction_part_size};
    
    for (size_t i = max_size; i-->0;)
    {
        const int a_shift{static_cast<int>(fraction_part_size(a) - fraction_part_size(b))};
        const int b_shift{static_cast<int>(fraction_part_size(b) - fraction_part_size(a))};
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

bool num::operator==(const num& p_other) const
{
    num a = (*this); a.trim(); a.check_separator();
    num b = p_other; b.trim(); b.check_separator();

    if (digit_count(a) != digit_count(b))
    {
        return false;
    }

    if (fraction_part_size(a) != fraction_part_size(b))
    {
        return false;
    }

    if (whole_part_size(a) != whole_part_size(b))
    {
        return false;
    }

    for (size_t i = 0; i < digit_count(a); i++)
    {
        if (a.data[i] != b.data[i])
        {
            return false;
        }
    }

    return true;
}

bool num::operator!=(const num& p_other) const
{
    return !(operator==(p_other));
}

fundamental_t to_fundamental(const num& p_num)
{
    fundamental_t result{0};
    for (size_t i = 0; i < digit_count(p_num); ++i)
    {
        result += p_num[i] * pow(10, i);
    }
    result /= pow(10, (digit_count(p_num) - p_num.separator));
    result *= static_cast<int>(p_num.sign) * 2 - 1;
    return result;
}

}

::rl::num operator"" _l(const char* p_str)
{
    return ::rl::num(p_str);
}