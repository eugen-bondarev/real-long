#include "rl/rl_number.h"
#include "rl/rl_common.h"

using rl::Number;

int main()
{
    Number a("98");
    Number b("2");

    a.print();
    b.print();

    auto c = a + b;
    c.print();

    return 0;
}