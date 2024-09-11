#pragma once

#include "aoc-day.hpp"

namespace day2 {
	#define NUMBER_IDX 5
	
	#define COUNT_RED 12
	#define COUNT_GREEN 13 
	#define COUNT_BLUE 14 
	
	typedef struct {
		int gameId;
		std::vector<std::array<int, 3>> rounds;
		bool  isPossible;
	
	} Game ;
	
	std::vector<std::string> split_str(std::string_view string, const char* splitter);

	std::string part1(std::ifstream& input);
	std::string part2(std::ifstream& input);

	extern Day day;
}

