#include "rl/rl_number.h"
#include "rl/rl_common.h"

using rl::Number;

int main()
{
    const Number a = "1";
    const Number b = "0";
    const Number c = a + b;

    a.print();
    b.print();
    c.print();

    return 0;
}