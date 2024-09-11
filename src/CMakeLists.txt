add_library(aoc-day ${CMAKE_CURRENT_SOURCE_DIR}/aoc-day.cpp)

add_library(day1 ${CMAKE_CURRENT_SOURCE_DIR}/day1.cpp)

add_executable(aoc ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_link_libraries(day1 PUBLIC aoc-day)
#target_link_libraries(day2 PUBLIC aoc-day)
#target_link_libraries(day3 PUBLIC aoc-day)
# target_link_libraries(day4 PUBLIC aoc-day)
# target_link_libraries(day5 PUBLIC aoc-day)
# target_link_libraries(day6 PUBLIC aoc-day)
# target_link_libraries(day7 PUBLIC aoc-day)
# target_link_libraries(day8 PUBLIC aoc-day)
# target_link_libraries(day9 PUBLIC aoc-day)
# 
# target_link_libraries(day10 PUBLIC aoc-day)
# target_link_libraries(day11 PUBLIC aoc-day)
# target_link_libraries(day12 PUBLIC aoc-day)
# target_link_libraries(day13 PUBLIC aoc-day)
# target_link_libraries(day14 PUBLIC aoc-day)
# target_link_libraries(day15 PUBLIC aoc-day)
# target_link_libraries(day16 PUBLIC aoc-day)
# target_link_libraries(day17 PUBLIC aoc-day)
# target_link_libraries(day18 PUBLIC aoc-day)
# target_link_libraries(day19 PUBLIC aoc-day)
# 
# target_link_libraries(day20 PUBLIC aoc-day)
# target_link_libraries(day21 PUBLIC aoc-day)
# target_link_libraries(day22 PUBLIC aoc-day)
# target_link_libraries(day23 PUBLIC aoc-day)
# target_link_libraries(day24 PUBLIC aoc-day)
# target_link_libraries(day25 PUBLIC aoc-day)

target_link_libraries(aoc PRIVATE day1)


#set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/bin)
install(TARGETS aoc)
