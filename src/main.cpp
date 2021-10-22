#include "rl/rl_number.h"
#include "rl/rl_common.h"

using rl::Number;

int main()
{
    Number a = "99.0";
    Number b = "5.0";
    Number c = a - b;

    a.print();
    b.print();
    c.print();

    return 0;
}