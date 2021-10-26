#include "rl_common.h"

namespace rl {

size_t division_precision{RL_DEFAULT_DIVISION_PRECISION};

size_t get_division_precision()
{
    return division_precision;
}

void set_division_precision(const size_t p_precision)
{
    division_precision = p_precision;
}

void set_default_division_precision()
{
    division_precision = RL_DEFAULT_DIVISION_PRECISION;
}

}