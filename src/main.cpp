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
        rl::fundamental_t cf = af * bf;
        
        num a = std::to_string(af);
        num b = std::to_string(bf);
        num c = a * b;

        if (p_logging)
        {
            RL_LINE_OUT(af << " - " << bf << " = " << cf);
            RL_LINE_OUT(rl::to_string(a) << " - " << rl::to_string(b) << " = " << rl::to_string(c));
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
            p_start = p_start * 0.5_l;
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
}

int main()
{
    srand(time(nullptr));
    
    // rl::print((25_l).pow(25_l * 25_l));

    // for (num i = 0_l; i < 100_l; i = i + 1_l)
    // {
    //     sequence_t sequence = collatz_conjecture((10_l).pow(75_l) + i * 2_l);
    // }

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

    // perform_tests<true>();

    // num a = 0.00012383_l;
    // num b = 5_l;
    // a *= a; a *= a; a *= a;
    // num c = a * b;

    // rl::print(a);
    // rl::print(b);
    // rl::print(c);

    num a = 1_l;
    num b = 0.0125_l;
    num c = a / b;
    rl::print(c);

    return 0;
}