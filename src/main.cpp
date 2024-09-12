#include <chrono>
#include <iostream>
#include <argp.h>
#include <vector>
#include <unistd.h>

#include "../include/aoc-day.hpp"
#include "../include/day1.hpp"
#include "../include/day2.hpp"

int main(int argc, char** argv){
	// -f !:FILE
	// -d :DAY
	// -a ALL
	// -v VERBOSE
	// -p ANS
	// -t TIME
	//
	
	int opt;
	
	bool all_flg = true;
	bool day_flg = false;
	bool verbos_flg = false;
	bool ans_flg = true;
	bool tim_flg = false;

	int day_id = 0;
	while((opt = getopt(argc, argv, ":f:ad:")) != -1){
		//std::cout << "optarg: " << opt  << " " << static_cast<char>(opt) << " " << optarg << "\n";
		switch (opt) {
			case 'f':
				if(!std::filesystem::exists(std::filesystem::current_path().append(optarg))){
					std::cout << "FILE " << std::quoted(optarg) << " does not exist\n";
					return EXIT_FAILURE;
				}
				Day::set_bin_path(optarg);
				break;
			case 'd':
				all_flg = false;
				day_flg = true;
				day_id = std::atoi(optarg);
				if (day_id < 0 || day_id > 25) {
					std::cout << "Date " << std::quoted(std::to_string(day_id)) << " out of range" << "\n";
					return EXIT_FAILURE;
				}
				day_id -= 1;
				break;
			case 'a':
				if (!day_flg) {
					all_flg = true;
				}
				break;
			case 'v':
				ans_flg = true;
				tim_flg = true;
				break;
			case 'p':
				break;
			case 't':
				tim_flg = true;
				break;
			case '?':
				std::cout << "unknown arg: " << optopt << " " << static_cast<char>(optopt) << "\n";
				return EXIT_FAILURE;
				break;
			case ':':
				std::cout << "missing arg for: " << optopt << " " << static_cast<char>(optopt) << "\n";
				return EXIT_FAILURE;
				break;
			default:
				break;
		}
	}

	std::vector<Day*> d;

	d.push_back(&day1::day);
	d.push_back(&day2::day);

	if (all_flg) {
		for (const auto& elem : d) {
			elem->run_part(1);
			elem->run_part(2);
			std::cout << "Day" << elem->get_day_id() << " 1 " << " Ans " << elem->get_ans_part(1) << "\n";
			std::cout << "Day" << elem->get_day_id() << " 2 " << " Ans " << elem->get_ans_part(2) << "\n";
		}
	}
	else {
		d.at(day_id)->run_part(1);
		d.at(day_id)->run_part(2);
		std::cout << "Day" << d.at(day_id)->get_day_id() << " 1 " << " Ans " << d.at(day_id)->get_ans_part(1) << "\n";
		std::cout << "Day" << d.at(day_id)->get_day_id() << " 2 " << " Ans " << d.at(day_id)->get_ans_part(2) << "\n";
	}

	return EXIT_SUCCESS;
}
