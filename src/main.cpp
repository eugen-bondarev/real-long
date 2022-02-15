#include "rl/rl_metrics.h"
#include "rl/rl_number.h"
#include "rl/rl_common.h"

#include <fstream>
#include <array>

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
    sequence_t result{};

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

sequence_t fibonacci(const std::array<num, 2>& p_start, const num& end) 
{
    sequence_t result = { p_start[0], p_start[1] };
    num current = result[0] + result[1];
    result.push_back(current);
    while (current < end) 
    {
        current = result[result.size() - 1] + result[result.size() - 2];
        result.push_back(current);
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
    for (num k = 0_l; k < p_precision; ++k)
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
        // RL_LINE_OUT(rl::to_string(
        //     (50_l).pow(99_l)
        // ));

        // RL_LINE_OUT("\n");

        // RL_LINE_OUT(rl::to_string( 
        //     (99_l).factorial()
        // ));

        const sequence_t fibonacci_sequence = fibonacci({ 1_l, 1_l }, 100000000000000000000000000000000000000000000000000000000000_l);
        print(fibonacci_sequence);

        // num fib = fibonacci(3340368);
        // rl::print(fib);
        // return 0;

        // num a = 1_l / 6_l;
        // rl::print(a);

        // perform_tests<true>();

        // rl::set_division_precision(100);
        
        // rl::Timer timer;
        //     num e = get_e(1000_l);
        // RL_VAR_OUT(timer.get_delta());
        // rl::print(e);

        // rl::print((25_l).pow(25_l * 25_l));

        // struct Data
        // {
        //     num start;
        //     size_t size;
        // };

        // rl::vec_t<Data> recording; recording.reserve(5000);

        // for (size_t i = 1; i < fib.size(); ++i)
        // {
        //     const num start{fib[i]};
        //     const size_t size = collatz_conjecture(start).size();
        //     recording.push_back({ start, size });
        // }

        // std::ofstream file("C:/Users/azare/Documents/Dev/Cpp/real-long/recording");

        // if (!file.is_open())
        // {
        //     return 0;
        // }

        // for (size_t i = 0; i < recording.size(); i++)
        // {
        //     file << rl::to_string(recording[i].start) << ",";
        //     file << recording[i].size << '\n';
        // }

        // file.close();

        // const num start{(25_l).factorial() + 1_l};
        // rl::print(start);
        // const sequence_t sequence = collatz_conjecture(start);
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