cmake_minimum_required(VERSION 3.15)

project(aoc)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_GENERATOR Ninja)

add_executable(one.out src/one.cpp)
add_executable(two.out src/two.cpp)

