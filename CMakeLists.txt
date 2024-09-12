cmake_minimum_required(VERSION 3.28)
project(advent-of-code-23)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wpedantic -Wall -Wextra -pg)
add_link_options(-pg)

# Later move this into a script file
set(SOURCE_FILES
	src/main.cpp
	src/aoc-day.cpp include/aoc-day.hpp
	src/day1.cpp include/day1.hpp
	src/day2.cpp include/day2.hpp
	src/day3.cpp include/day3.hpp
	src/day4.cpp include/day4.hpp
	src/day5.cpp include/day5.hpp
)

message("${SOURCE_FILES}")

add_executable(aoc ${SOURCE_FILES})

add_custom_command(
	TARGET aoc POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${CMAKE_SOURCE_DIR}/inputs
	${CMAKE_BINARY_DIR}/inputs
)
