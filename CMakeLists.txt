cmake_minimum_required(VERSION 3.28)
project(advent-of-code-23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_GENERATOR "Ninja")
add_compile_options(-Wpedantic -Wall -Wextra -pg)
add_link_options(-pg)

add_subdirectory(src)
