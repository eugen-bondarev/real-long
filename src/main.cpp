#include "rl/rl_number.h"
#include "rl/rl_common.h"

using rl::Number;

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
        
        Number a = std::to_string(af);
        Number b = std::to_string(bf);
        Number c = a - b;

        if (p_logging)
        {
            RL_LINE_OUT(af << " - " << bf << " = " << cf);
            RL_LINE_OUT(a.to_string() << " - " << b.to_string() << " = " << c.to_string());
            RL_LINE_OUT("error: " << (std::abs(c.to_fundamental()) - std::abs(cf)));
        }

        error += std::abs(c.to_fundamental()) - std::abs(cf);
    }

    RL_VAR_OUT(error);
}

int main()
{
    srand(time(nullptr));

    // perform_tests<false>();

    Number a = "5";
    Number b = "-10";
    Number c = a - b;

    a.print();
    b.print();
    c.print();

    return 0;
}