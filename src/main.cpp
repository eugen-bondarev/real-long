#include "common.h"

#include "number.h"

void tests()
{
    const size_t amount_of_tests{1000};
    size_t right{0};

    for (size_t i = 0; i < amount_of_tests; i++)
    {
        fundamental_t a_0 = rand();
        fundamental_t b_0 = rand();

        Number a_1(std::to_string(a_0));
        Number b_1(std::to_string(b_0));

        fundamental_t c_0 = a_0 + b_0;
        Number c_1 = a_1 + b_1;

        if (c_1.get_fundamental() == c_0) right++;
    }

    VAR_OUT(right);
    VAR_OUT(amount_of_tests);
    VAR_OUT(right / static_cast<float>(amount_of_tests));
}

int main()
{
    Number a("5000000000000000000000000000000000000000000000000000");
    Number b("154");
    Number c = a * b;
    c.print_out();

    return 0;
}