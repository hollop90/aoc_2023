add_executable(one.out src/one.cpp)
add_executable(two.out src/two.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

