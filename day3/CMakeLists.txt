file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_library(part_one)
target_sources(part_one PUBLIC include/part_one.cpp)
target_include_directories(part_one PUBLIC include)

add_executable(solution src/main.cpp)
target_link_libraries(solution part_one)
