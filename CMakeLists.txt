cmake_minimum_required(VERSION 3.28)
project(aoc CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_GENERATOR "Ninja")
add_compile_options(-pedantic -Wall -Wextra -pg)
add_link_options(-pg)

add_subdirectory(day1)
add_subdirectory(day3)
