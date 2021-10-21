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

        fundamental_t c_0;
        Number c_1;

        if (a_0 > b_0)
        {
            c_0 = a_0 - b_0;
            c_1 = a_1 - b_1;
        }
        else
        {
            c_0 = b_0 - a_0;
            c_1 = b_1 - a_1;
        }

        // fundamental_t c_0 = a_0 * b_0;
        // Number c_1 = a_1 * b_1;

        if (c_1.get_fundamental() == c_0) right++;
    }

    VAR_OUT(right);
    VAR_OUT(amount_of_tests);
    VAR_OUT(right / static_cast<float>(amount_of_tests));
}

using sequence_t = std::vector<Number>;

sequence_t create_sequence(Number p_n)
{
    sequence_t sequence{p_n};

    // p_n.print_out();
    // std::cout << ' ';

    while (p_n != Number("1"))
    {
        if (p_n.is_even())
        {
            p_n = p_n / Number("2");
        }
        else
        {
            p_n = p_n * Number("3") + Number("1");
        }
        sequence.push_back(p_n);
    }

    return sequence;
}

void log_out(const sequence_t& p_sequence)
{
    for (size_t i = 0; i < p_sequence.size(); i++)
    {
        p_sequence[i].print_out(); std::cout << ' ';
    }
}

int main()
{
    sequence_t sequence_0 = create_sequence(Number("2").pow(10000) - Number("2"));
    VAR_OUT(sequence_0.size());
    sequence_t sequence_1 = create_sequence(Number("2").pow(10000) - Number("3"));
    VAR_OUT(sequence_1.size());
    sequence_t sequence_2 = create_sequence(Number("2").pow(10000) - Number("4"));
    VAR_OUT(sequence_2.size());

    return 0;
}