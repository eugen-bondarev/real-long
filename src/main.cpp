#include "rl/rl_number.h"
#include "rl/rl_common.h"

using rl::Number;

int main()
{
    Number a = "10";
    Number b = "20";
    Number c = a - b;

    a.print();
    b.print();
    c.print();

    return 0;
}