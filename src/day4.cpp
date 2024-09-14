#include "../include/day4.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

namespace day4 {
	const size_t SEPARATOR_IDX = 40;
	const size_t COLON_IDX = 8;
	std::string part1(std::ifstream& input){
		std::vector<std::string> cards;
		std::vector<int64_t> cardsPoints;

		{
			std::string out;
			while (std::getline(input, out)) {
				if (!out.empty()) {
					cards.push_back(out);
				}
			}
		}

		const int64_t numCards = cards.size();
		const int64_t cardLen = cards.front().size();

		for (int64_t cardsRow = 0; cardsRow < numCards; cardsRow++) {
			std::vector<int> winningNums;
			std::stringstream winSS(cards.at(cardsRow).substr(COLON_IDX+1, SEPARATOR_IDX-(COLON_IDX+2)));
			{
				int out;
				while (winSS) {
					winSS >> out;
					if (out != -1) {
						winningNums.push_back(out);
					}
					out = -1;
				}
			}
			std::cout << "Card num " << cardsRow+1 << " winning numbers" << ":\n";
			for (const auto& i : winningNums) {
				std::cout << i << "\n";
			}
			std::cout << "\n";

			std::vector<int> potentialNums;
			std::stringstream potSS(cards.at(cardsRow).substr(SEPARATOR_IDX+2));
			{
				int out;
				while (potSS) {
					potSS >> out;
					if (out != -1) {
						potentialNums.push_back(out);
					}
					out = -1;
				}
			}
			std::cout << "Card num " << cardsRow+1 << " potential numbers" << ":\n";
			for (const auto& i : potentialNums) {
				std::cout << i << "\n";
			}
			std::cout << "\n";

			int totalFound = 0;
			int points = 1;
			for (const auto i : potentialNums) {
				if (std::find(winningNums.begin(), winningNums.end(), i) != winningNums.end()) {
					totalFound++;
					std::cout << "found " << i << "\n";
					if (totalFound > 1) {
						points *= 2;
					}
				}
			}
			if (totalFound != 0) {
				cardsPoints.push_back(points);
			}
			else {
				points = 0;
			}
			std::cout << "Card num " << cardsRow+1 << " total points" << ":\n";
			std::cout << points << "\n";
			std::cout << "\n";
		}

		return std::to_string(std::accumulate(cardsPoints.begin(), cardsPoints.end(), 0));
	}

	std::string part2(std::ifstream& input){
		return std::to_string(0);
	}
	Day day(4, &part1, &part2);
}

