#include "../include/day3.hpp"

#include <cassert>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

namespace day3 {
	std::vector<int> check_vert(const int dir, const std::vector<std::string>& vec, const int64_t line, const int64_t col){
		assert(dir >= -1 && dir <= 1);
		const int64_t numLines = vec.size();
		const int64_t lineLen = vec.front().size();

		const int64_t begin = (col - 1) < 0 ? 0 : (col- 1);
		const int64_t end = (col + 1) == lineLen ? (col) : (col+ 1);

		std::vector<int> nums;

		if (line+dir < numLines && line+dir >= 0) {
			for (int64_t i = begin; i < end + 1; i++) {
				if (std::isdigit(vec.at(line+dir).at(i))) {
					int64_t j = i;
					while (std::isdigit(vec.at(line+dir).at(j))) {
						--j;
						if (j < 0) {
							break;
						}
					}
					bool consecutive = false;
					if (i != begin && std::isdigit(vec.at(line+dir).at(i-1))) {
						consecutive = true;
					}
					if (!consecutive) {
						nums.push_back(std::atoi(vec.at(line+dir).substr(j+1).c_str()));
					}
				}
			}
			return nums;
		}
		return nums;
	}

	// ... any number adjacent to a symbol, even diagonally,
	// is a "part number" and should be included in your sum.
	// What is the sum of all of the part numbers in the engine schematic?
	std::string part1(std::ifstream& in){
		std::vector<int> validPartNums;

		std::vector<std::string> a;

		std::string line;
		while (std::getline(in, line)) {
			if (line.empty()) {
				break;
			}
			a.push_back(line);
		}

		for (size_t i = 0; i < a.size(); i++) {
			for (size_t lineIdx = 0; lineIdx < a.at(i).length(); lineIdx++) {
				if (std::isdigit(a.at(i).at(lineIdx))) {
					// It's ugly, it's inefficient, but it works and that's all that matters for now
					int partNum = std::atoi(a.at(i).substr(lineIdx, std::string::npos).c_str());	

					std::stringstream ss;
					ss << partNum;

					std::string s;
					ss >> s;
					int partNumLen = s.length();

					const size_t begin = (lineIdx-1) == SIZE_MAX ? 0 : lineIdx-1;
					const size_t end = (lineIdx+partNumLen) > a.size()-1 ? a.size()-1 : lineIdx+partNumLen;

					bool found = false;

					// above
					if ((i-1) != SIZE_MAX) {
						for (size_t symIdx = begin; symIdx < end+1; symIdx++) {
							if (a.at(i-1).at(symIdx) != '.' && !std::isdigit(a.at(i-1).at(symIdx))) {
								found = true;
								validPartNums.push_back(partNum);	
								break;
							}	
						}
						if (found) {
							lineIdx += partNumLen;
							continue;
						}
					}

					// inline
					if (a.at(i).at(begin) != '.' && !std::isdigit(a.at(i).at(begin))) {
								found = true;
						validPartNums.push_back(partNum);	
					}	
					if (found) {
						lineIdx += partNumLen;
						continue;
					}

					if (a.at(i).at(end) != '.' && !std::isdigit(a.at(i).at(end))) {
								found = true;
						validPartNums.push_back(partNum);	
					}	
					if (found) {
						lineIdx += partNumLen;
						continue;
					}

					// below
					if ((i+1) < a.at(i).size()) {
						for (size_t symIdx = begin; symIdx < end+1; symIdx++) {
							if (a.at(i+1).at(symIdx) != '.' && !std::isdigit(a.at(i+1).at(symIdx))) {
								found = true;
								validPartNums.push_back(partNum);	
								break;
							}	
						}
						if (found) {
							lineIdx += partNumLen;
							continue;
						}
					}
					lineIdx += partNumLen;
				}
			}
		}
		// for (const auto& elem : validPartNums) {
		// 	std::clog << "valid num: " << elem << "\n";
		// }
		int sum = std::accumulate(validPartNums.begin(), validPartNums.end(), 0);

		return std::to_string(sum);
	}

	// A gear is any * symbol that is adjacent to exactly two part numbers.
	// Its gear ratio is the result of multiplying those two numbers together.
	//
	// What is the sum of all of the gear ratios in your engine schematic?
	std::string part2(std::ifstream& input){
		// Store the gear ratios
		std::vector<int64_t> ans;

		// The "schematic"
		std::vector<std::string> schema;
		{
			std::string out;
			while (std::getline(input, out)) {
				if (!out.empty()) {
					schema.push_back(out);
				}
			}
		}

		const int64_t linLen = schema.front().size();
		const int64_t totLines = schema.size();

		// scan each line for a '*'
		// if found, check around it for numbers (with bounds checking)
		// parse numbers
		// count how many numbers are found
		// if count is > 2 go on to next '*' 
		// else get product of numbers and save
		// repeat

		for (int64_t lineNum = 0; lineNum < totLines; lineNum++) {
			for (int64_t colNum = 0; colNum < linLen; colNum++) {
				auto c = schema.at(lineNum).at(colNum);

				if (c == '*') {
					std::vector<int> nearbyNums;

					// Check ABOVE
					for (const auto& elem : check_vert(-1, schema, lineNum, colNum)) {
						nearbyNums.push_back(elem);
					}

					// Check INLINE
					for (const auto& elem : check_vert(0, schema, lineNum, colNum)) {
						nearbyNums.push_back(elem);
					}

					// Check BELOW
					for (const auto& elem : check_vert(4, schema, lineNum, colNum)) {
						nearbyNums.push_back(elem);
					}

					if (nearbyNums.size() == 2) {
						ans.push_back(nearbyNums.at(0) * nearbyNums.at(1));
					}
				}
			}	
		}
		return std::to_string(std::accumulate(ans.begin(), ans.end(), 0));
	}

	Day day(3, &part1, &part2);
}

