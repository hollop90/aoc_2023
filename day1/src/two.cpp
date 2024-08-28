#include <algorithm>
#include <array>
#include <numeric>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

std::pair<std::size_t, int> findFirstWord(std::string_view line);
std::pair<std::size_t, int> findLastWord(std::string_view line);

std::array<std::pair<std::string, int>, 9> words = {
	    std::make_pair("one", 1),
	    std::make_pair("two", 2),
	    std::make_pair("three", 3),
	    std::make_pair("four", 4),
	    std::make_pair("five", 5),
	    std::make_pair("six", 6),
	    std::make_pair("seven", 7),
	    std::make_pair("eight", 8),
	    std::make_pair("nine", 9)
    };

int main(){
	std::ifstream puzzle_input;
	std::string currLine;
	std::vector<int> parsedNumbers;
	std::vector<std::string::iterator> parsedWordsIter;

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
			
			auto firstIterDigit = std::find_if(currLine.begin(), currLine.end(), [](char c) {
					return std::isdigit(c);
					});

			auto lastIterDigit = std::find_if(currLine.rbegin(), currLine.rend(), [](char c) {
					return std::isdigit(c);
					});

			std::cout << "Found digits:\n";
			std::cout << *firstIterDigit << "\n";
			std::cout << *lastIterDigit << "\n";

			auto [firstIterWordDistance, firstIterWordDigit] = findFirstWord(currLine);
			auto [lastIterWordDistance, lastIterWordDigit] = findLastWord(currLine);

			std::cout << "Found word digits:\n";
			std::cout << firstIterWordDigit << "\n";
			std::cout << lastIterWordDigit << "\n";

			// ASCII conversion from code to digit
			int firstRealDigit = std::distance(currLine.begin(), firstIterDigit) < firstIterWordDistance ? *firstIterDigit-48 : firstIterWordDigit;
			int lastRealDigit = std::distance(currLine.rbegin(), lastIterDigit) < lastIterWordDistance ? *lastIterDigit-48 : lastIterWordDigit;

			std::cout << "Found real digits:\n";
			std::cout << firstRealDigit << "\n";
			std::cout << lastRealDigit << "\n";

			int finalNum = firstRealDigit*10 + lastRealDigit;
			parsedNumbers.push_back(finalNum);
			std::cout << "Final Number: " << finalNum << "\n\n";
		}
	}
		auto finalSum = std::accumulate(parsedNumbers.begin(), parsedNumbers.end(), 0);
		std::cout << "FINAL SUM: " << finalSum << "\n";
		return 0;
}

std::pair<std::size_t, int> findFirstWord(const std::string_view line){
	std::pair<std::size_t, int> firstWord{std::distance(line.begin(), line.end()), 0};
	for (const auto& elem : words) {
		auto currIter = std::search(line.begin(), line.end(), elem.first.begin(), elem.first.end());
		if (std::distance(line.begin(), currIter) < firstWord.first) {
			firstWord.first = std::distance(line.begin(), currIter);
			firstWord.second = elem.second;
		}
	}
	return firstWord;
}

std::pair<std::size_t, int> findLastWord(std::string_view line){
	std::pair<std::size_t, int> firstWord{std::distance(line.rbegin(), line.rend()), 0};
	for (const auto& elem : words) {
		auto currIter = std::search(line.rbegin(), line.rend(), elem.first.rbegin(), elem.first.rend());
		if (std::distance(line.rbegin(), currIter) < firstWord.first) {
			firstWord.first = std::distance(line.rbegin(), currIter);
			firstWord.second = elem.second;
		}
	}
	return firstWord;
}
