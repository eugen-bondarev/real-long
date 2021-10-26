#include "rl/rl_number.h"
#include "rl/rl_common.h"

using rl::num;

float gen_rand(float p_from, float p_to)
{
    return rand() / static_cast<float>(RAND_MAX) * (p_to - p_from) + p_from;
}

template <bool p_logging>
void perform_tests()
{
    const size_t test_count{1000};
    float error{0};

    for (size_t i = 0; i < test_count; i++)
    {
        rl::fundamental_t af = gen_rand(-1000, 1000);
        rl::fundamental_t bf = gen_rand(-1000, 1000);
        rl::fundamental_t cf = af / bf;
        
        num a = std::to_string(af);
        num b = std::to_string(bf);
        num c = a / b;

        if (p_logging)
        {
            RL_LINE_OUT(af << " / " << bf << " = " << cf);
            RL_LINE_OUT(rl::to_string(a) << " / " << rl::to_string(b) << " = " << rl::to_string(c));
            RL_LINE_OUT("error: " << (std::abs(rl::to_fundamental(c)) - std::abs(cf)));
        }

        error += std::abs(rl::to_fundamental(c)) - std::abs(cf);
    }

    RL_VAR_OUT(error);
}

using sequence_t = rl::vec_t<num>;

sequence_t collatz_conjecture(num p_start)
{
    sequence_t result{p_start};

    while (p_start != 1_l)
    {
        if (rl::is_even(p_start))
        {
            p_start = p_start / 2_l;
        }
        else
        {
            p_start = p_start * 3_l + 1_l;
        }
        result.push_back(p_start);
    }

    return result;
}

void print(const sequence_t& p_sequence)
{
    for (size_t i = 0; i < p_sequence.size(); i++)
    {
        RL_LOG_OUT(rl::to_string(p_sequence[i]) << ' ');
    }
    RL_LOG_OUT('\n');
}

num get_pi(const num& p_precision)
{
    num pi{0_l};
    for (num k = 0_l; k < p_precision; k++)
    {
        num numerator = rl::take_negative(1_l).pow(k);
        num denominator = k * 2_l + 1_l;

        pi += numerator / denominator;
    }

    return pi * 4_l;
}

num get_e(const num& p_precision)
{
    num e{0_l};
    for (num k = 0_l; k < p_precision; k++)
    {
        e += 1_l / k.factorial();
    }

    return e;
}

int main()
{
    srand(time(nullptr));

    try
    {
        // num a = 1_l / 6_l;
        // rl::print(a);

        // perform_tests<true>();

        rl::set_division_precision(100);
        num e = get_e(500_l);
        rl::print(e);
        
        // rl::print((25_l).pow(25_l * 25_l));

        // sequence_t sequence = collatz_conjecture(9780657630_l * 4_l + 1_l);
        // print(sequence);
        // RL_VAR_OUT(sequence.size());

        // RL_VAR_OUT(rl::is_even(num("89")));
        // RL_VAR_OUT(rl::is_even(num("98")));

        // num a = num("99").factorial();
        // num b = num("50").pow("99");

        // rl::print(a);
        // rl::print(b);

        // num a = num("55").pow("99");
        // rl::print(a);

        // for (num i = "0"; i < "20"; i = i + "1")
        // {
        //     rl::print(i);
        // }

        // num a = 0.00012383_l;
        // num b = 5_l;
        // a *= a; a *= a; a *= a;
        // num c = a * b;

        // rl::print(a);
        // rl::print(b);
        // rl::print(c);

        // num a = "25";
        // num b = "-4.35";

        // rl::set_division_precision(25);
        // num c = a / b;

        // rl::set_division_precision(5000);
        // num d = a / b;

        // rl::print(c);
        // rl::print(d);

    } catch (const std::exception& p_e)
    {
        RL_LINE_OUT(p_e.what());
    }

    return 0;
}