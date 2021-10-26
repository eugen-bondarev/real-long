#include "rl_metrics.h"

#include <chrono>

namespace rl {

time_t get_time()
{        
    using namespace std::chrono;
    milliseconds ms = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
    );
    return ms.count();
}

time_t Timer::get_delta() const
{
    return get_time() - start;
}

}