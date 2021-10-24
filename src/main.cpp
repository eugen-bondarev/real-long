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
        rl::fundamental_t cf = af - bf;
        
        num a = std::to_string(af);
        num b = std::to_string(bf);
        num c = a - b;

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

int main()
{
    srand(time(nullptr));

    // perform_tests<true>();

    num a = "0.00012383";
    num b = "5";
    num c = a * b;

    rl::print(a);
    rl::print(b);
    rl::print(c);

    return 0;
}