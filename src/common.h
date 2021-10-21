#pragma once

#ifndef __COMMON_H__
#define __COMMON_H__

#include <iostream>
#include <typeinfo>

#define LOG_OUT(x) std::cout << x << std::endl
#define VAR_OUT(x) std::cout << typeid(x).name() << " " << #x << " = " << x << std::endl

#endif