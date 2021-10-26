#pragma once

namespace rl
{
    using time_t = long long;

    time_t get_time();

    struct Timer
    {
        time_t get_delta() const;

        time_t start{get_time()};
    };
}