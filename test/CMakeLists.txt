cmake_minimum_required(VERSION 3.16)

project(real-long VERSION 1.0.0)

add_executable(test test.cpp)

target_link_libraries(test PRIVATE real-long)