cmake_minimum_required(VERSION 3.16)

project(real-long VERSION 1.0.0)

file(GLOB_RECURSE src src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${src})

target_include_directories(
    ${PROJECT_NAME}
        PRIVATE
            src/rl
        INTERFACE
            src
)

add_subdirectory(test)