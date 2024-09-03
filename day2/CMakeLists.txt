cmake_minimum_required(VERSION 3.15)

project(aoc)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(solution.out src/main.cpp)
target_include_directories(solution.out PUBLIC include)
