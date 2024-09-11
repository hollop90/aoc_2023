#include <numeric>
#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../include/day1.hpp"

namespace day1 {
	std::string part1(std::ifstream& input){
		std::string currLine;
		std::vector<int> parsedNumbers;
	
		while(std::getline(input, currLine)){
			if (currLine.empty()) {
				break;
			}

			std::vector<char> foundDigits;
			//std::clog << "Current Line: " << currLine << "\n";
			for (auto const i : currLine) {
				if (std::isdigit(i)){
					foundDigits.push_back(i);
				}
			}
	
			//std::clog << "Found digits:\n";
			for (auto const elem : foundDigits){
				//std::clog << elem << "\n";
			}
	
			std::string tempStr = {foundDigits.front(), foundDigits.back()};
	
			int finalNum = std::atoi(tempStr.c_str());
			parsedNumbers.push_back(finalNum);
			//std::clog << "Final Number: " << finalNum << "\n\n";
		}
		return std::to_string(std::accumulate(parsedNumbers.begin(), parsedNumbers.end(), 0));
	}

	std::pair<std::int64_t, int> findFirstWord(std::string_view line);
	std::pair<std::int64_t, int> findLastWord(std::string_view line);
	
	// Note the "{{...}}" needed for this kind of initialization
	std::array<std::pair<std::string, int>, 9> words = {{
		{"one", 1},
		{"two", 2},
		{"three", 3},
		{"four", 4},
		{"five", 5},
		{"six", 6},
		{"seven", 7},
		{"eight", 8},
		{"nine", 9}
	}};

	std::string part2(std::ifstream& input){
		std::string currLine;
		std::vector<int> parsedNumbers;
		std::vector<std::string::iterator> parsedWordsIter;

		while(std::getline(input, currLine)){
			if (currLine.empty()) {
				break;
			}

			std::vector<char> foundDigits;
			//std::clog << "Current Line: " << currLine << "\n";
			
			auto firstIterDigit = std::find_if(currLine.begin(), currLine.end(), [](char c) {
					return std::isdigit(c);
					});

			auto lastIterDigit = std::find_if(currLine.rbegin(), currLine.rend(), [](char c) {
					return std::isdigit(c);
					});

			//std::clog << "Found digits:\n";
			//std::clog << *firstIterDigit << "\n";
			//std::clog << *lastIterDigit << "\n";

			auto [firstIterWordDistance, firstIterWordDigit] = findFirstWord(currLine);
			auto [lastIterWordDistance, lastIterWordDigit] = findLastWord(currLine);

			//std::clog << "Found word digits:\n";
			//std::clog << firstIterWordDigit << "\n";
			//std::clog << lastIterWordDigit << "\n";

			// ASCII conversion from code to digit
			int firstRealDigit = std::distance(currLine.begin(), firstIterDigit) < firstIterWordDistance ? *firstIterDigit-48 : firstIterWordDigit;
			int lastRealDigit = std::distance(currLine.rbegin(), lastIterDigit) < lastIterWordDistance ? *lastIterDigit-48 : lastIterWordDigit;

			//std::clog << "Found real digits:\n";
			//std::clog << firstRealDigit << "\n";
			//std::clog << lastRealDigit << "\n";

			int finalNum = firstRealDigit*10 + lastRealDigit;
			parsedNumbers.push_back(finalNum);
			//std::clog << "Final Number: " << finalNum << "\n\n";
		}
		return std::to_string(std::accumulate(parsedNumbers.begin(), parsedNumbers.end(), 0));
	}

	std::pair<std::int64_t, int> findFirstWord(const std::string_view line){
		std::pair<std::int64_t, int> firstWord{std::distance(line.begin(), line.end()), 0};
		for (const auto& elem : words) {
			auto currIter = std::search(line.begin(), line.end(), elem.first.begin(), elem.first.end());
			if (std::distance(line.begin(), currIter) < firstWord.first) {
				firstWord.first = std::distance(line.begin(), currIter);
				firstWord.second = elem.second;
			}
		}
		return firstWord;
	}
	
	std::pair<std::int64_t, int> findLastWord(std::string_view line){
		std::pair<std::int64_t, int> firstWord{std::distance(line.rbegin(), line.rend()), 0};
		for (const auto& elem : words) {
			auto currIter = std::search(line.rbegin(), line.rend(), elem.first.rbegin(), elem.first.rend());
			if (std::distance(line.rbegin(), currIter) < firstWord.first) {
				firstWord.first = std::distance(line.rbegin(), currIter);
				firstWord.second = elem.second;
			}
		}
		return firstWord;
	}

	Day day(1, &part1, &part2);
}
