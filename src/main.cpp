#include <chrono>
#include <iostream>
#include <argp.h>
#include <vector>

#include "../include/aoc-day.hpp"
#include "../include/day1.hpp"

int main(int argc, char** argv){
	std::vector<Day*> d;

	d.push_back(&day1::day);

	d.at(0)->run_part(1);

	namespace sc = std::chrono;
	std::cout << "Day 1 ANS: " << d.at(0)->get_ans_part(1) << "\n";
	std::cout << "Day 1 TIME: " << duration_cast<sc::microseconds>(d.at(0)->get_time_part(1)) << "\n";

	return EXIT_SUCCESS;
}
