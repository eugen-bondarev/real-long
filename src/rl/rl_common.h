#pragma once

#ifndef __RL_COMMON_H__
#define __RL_COMMON_H__

#include <stdexcept>
#include <iostream>
#include <string>
#include <vector>

namespace rl {

using str_t = std::string;

template <typename T>
using vec_t = std::vector<T>;

using digit_t = int;

using fundamental_t = float;

#define RL_LOG_OUT(x) std::cout << x
#define RL_VAR_OUT(x) std::cout << #x << " = " << x << std::endl
#define RL_LINE_OUT(x) std::cout << x << std::endl

}

#endif