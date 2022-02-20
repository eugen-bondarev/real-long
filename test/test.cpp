#include <rl/rl.h>

float gen_rand(float p_from, float p_to)
{
    return rand() / static_cast<float>(RAND_MAX) * (p_to - p_from) + p_from;
}

template <bool p_logging>
void perform_tests()
{
    const size_t test_count{25};
    float error{0};

    for (size_t i = 0; i < test_count; i++)
    {
        rl::fundamental_t af = gen_rand(-1000, 1000);
        rl::fundamental_t bf = gen_rand(-1000, 1000);
        rl::fundamental_t cf = af / bf;
        
        const rl::num a = std::to_string(af);
        const rl::num b = std::to_string(bf);
        const rl::num c = a / b;

        if (p_logging)
        {
            RL_LINE_OUT("C++ output: " << af << " / " << bf << " = " << cf);
            RL_LINE_OUT("rl output: " << rl::to_string(a) << " / " << rl::to_string(b) << " = " << rl::to_string(c));
            if (!isnan(error))
            {
                RL_LINE_OUT("Error: " << (std::abs(rl::to_fundamental(c)) - std::abs(cf)));
            }
            RL_LINE_OUT('\n');
        }

        error += std::abs(rl::to_fundamental(c)) - std::abs(cf);
    }

    if (!isnan(error))
    {
        RL_VAR_OUT(error);
    }
    RL_LINE_OUT("Passed.");
}

using sequence_t = rl::vec_t<rl::num>;

sequence_t collatz_conjecture(rl::num p_start)
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

sequence_t fibonacci(const std::array<rl::num, 2>& p_start, const rl::num& end) 
{
    sequence_t result = { p_start[0], p_start[1] };
    rl::num current = result[0] + result[1];
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

rl::num get_pi(const rl::num& p_precision)
{
    rl::num pi{0_l};
    for (rl::num k = 0_l; k < p_precision; k++)
    {
        rl::num numerator = rl::take_negative(1_l).pow(k);
        rl::num denominator = k * 2_l + 1_l;

        pi += numerator / denominator;
    }

    return pi * 4_l;
}

rl::num get_e(const rl::num& p_precision)
{
    rl::num e{0_l};
    for (rl::num k = 0_l; k < p_precision; ++k)
    {
        e += 1_l / k.factorial();
    }

    return e;
}

int main() 
{
    perform_tests<true>();
    
    RL_LINE_OUT('\n');

    RL_LINE_OUT("55^99 = " << rl::to_string(
        (55_l).pow(99_l)
    ));

    RL_LINE_OUT('\n');
    
    RL_LINE_OUT("99! = " << rl::to_string(
        (99_l).factorial()
    ));

    std::cin.get();

    return 0;
}