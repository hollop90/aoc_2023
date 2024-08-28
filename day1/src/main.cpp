#include <algorithm>
#include <numeric>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

int64_t totalSum = {};

int64_t parseLine(std::string_view line);

auto is_num = [](char c) -> bool { 
	return std::isdigit(c); 
};

int main(){
	std::ifstream puzzle_input;
	std::string currLine;
	std::vector<int> parsedNumbers;

	puzzle_input.open("input.txt");

	if (!puzzle_input.is_open()) {
		std::cerr << "Failed to open file\n";
		std::exit(EXIT_FAILURE);
	}
	else {
		while(std::getline(puzzle_input, currLine)){
			if (currLine.empty()) {
				break;
			}
			std::vector<char> foundDigits;
			std::cout << "Current Line: " << currLine << "\n";
			for (auto const i : currLine) {
				if (is_num(i)){
					foundDigits.push_back(i);
				}
			}

			std::cout << "Found digits:\n";
			for (auto const elem : foundDigits){
				std::cout << elem << "\n";
			}

			std::string tempStr = {foundDigits.front(), foundDigits.back()};

			int finalNum = std::atoi(tempStr.c_str());
			parsedNumbers.push_back(finalNum);
			std::cout << "Final Number: " << finalNum << "\n\n";
		}
	}
		auto finalSum = std::accumulate(parsedNumbers.begin(), parsedNumbers.end(), 0);
		std::cout << "FINAL SUM: " << finalSum << "\n";
		std::exit(EXIT_SUCCESS);
}
