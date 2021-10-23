#include "rl/rl_number.h"
#include "rl/rl_common.h"

using rl::Number;

int main()
{
    Number a = "25";
    Number b = "25.0000000000000001";
    Number c = a - b;

    a.print();
    b.print();
    c.print();

    return 0;
}