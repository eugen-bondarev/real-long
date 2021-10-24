#include "rl/rl_number.h"
#include "rl/rl_common.h"

using rl::Number;

void tests()
{
    const size_t test_count{1000};
    float error{0};

    for (size_t i = 0; i < test_count; i++)
    {
        rl::fundamental_f_t af = rand() / static_cast<float>(RAND_MAX) * 10;
        rl::fundamental_f_t bf = rand() / static_cast<float>(RAND_MAX) * 10;
        rl::fundamental_f_t cf = af + bf;
        
        Number a = std::to_string(af);
        Number b = std::to_string(bf);
        Number c = a + b;

        RL_LINE_OUT(af << " - " << bf << " = " << cf);
        RL_LINE_OUT(a.to_string() << " - " << b.to_string() << " = " << c.to_string());
        RL_LINE_OUT("error: " << (std::abs(c.get_fundamental()) - std::abs(cf)));

        error += std::abs(c.get_fundamental()) - std::abs(cf);
    }

    RL_VAR_OUT(error);
}

int main()
{
    tests();
    // Number a = "8";
    // Number b = "7.5";
    // Number c = a - b;

    // a.print();
    // b.print();
    // c.print();

    return 0;
}