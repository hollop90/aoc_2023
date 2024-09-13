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

		// Convenience variables
		const int64_t linLen = schema.front().size();
		const int64_t totLines = schema.size();

		//check
		// for (const auto& i : schema) {
		// 	std::clog << i << "\n";
		// }

		// scan each line for a '*'
		// if found, check around it for numbers (with bounds checking)
		// parse numbers
		// count how many numbers are found
		// if count is > 2 go on to next '*' 
		// else get product of numbers and save
		//
		// repeat

		// Iterate throught lines
		for (int64_t lineNum = 0; lineNum < totLines; lineNum++) {
				//std::clog << schema[lineNum][colNum] << "\n";
			// Iterate through columns
			for (int64_t colNum = 0; colNum < linLen; colNum++) {
				//std::clog << schema[lineNum][colNum] << "\n";
				// Currenct character
				auto c = schema.at(lineNum).at(colNum);

				// Look around the '*' character
				//
				// | => begin
				// V
				// ... => above
				// .*. => inline
				// ... => below
				//   ^
				//   | => end
				//
				// A lot of boundry checking and liberal use of '.at()' is at play here
				// Thanks to how nested the code is and copy paste errors, I spent some
				// time tracking down "out of range" exceptions. Without '.at()' I would
				// just be looking at random memory
				if (c == '*') {
					const int64_t begin = (colNum - 1) < 0 ? 0 : (colNum - 1);
					const int64_t end = (colNum + 1) == linLen ? (colNum) : (colNum + 1);

					std::vector<int> nearbyNums;

					// Check ABOVE
					// if ((lineNum - 1) > 0 ){
					// 	for (int64_t i = begin; i < end + 1; i++) {
					// 		if (std::isdigit(schema.at(lineNum-1).at(i))) {
					// 			int64_t j = i;
					// 			while (std::isdigit(schema.at(lineNum-1).at(j))) {
					// 				--j;
					// 				if (j < 0) {
					// 					break;
					// 				}
					// 			}
					// 			bool consecutive = false;
					// 			if (i != begin && std::isdigit(schema.at(lineNum-1).at(i-1))) {
					// 				consecutive = true;
					// 			}
					// 			if (!consecutive) {
					// 				nearbyNums.push_back(std::atoi(schema.at(lineNum-1).substr(j+1).c_str()));
					// 			}
					// 		}
					// 	}
					// 	//std::clog << "linenum: " << lineNum << "\n";
					// }
					auto above = check_vert(-1, schema, lineNum, colNum);
					for (const auto& elem : above) {
						nearbyNums.push_back(elem);
					}

					// Check INLINE
					//std::clog << schema[lineNum][begin] << "\n";
					// if(std::isdigit(schema.at(lineNum).at(begin))){
					// 	int64_t j = begin;
					// 	while (std::isdigit(schema.at(lineNum).at(j))) {
					// 		--j;
					// 		if (j < 0) {
					// 			break;
					// 		}
					// 	}
					// 	nearbyNums.push_back(std::atoi(schema.at(lineNum).substr(j+1).c_str()));
					// }
					auto left = check_vert(0, schema, lineNum, colNum);
					for (const auto& elem : left) {
						nearbyNums.push_back(elem);
					}
					//std::clog << schema[lineNum][end] << "\n";
					// if(std::isdigit(schema.at(lineNum).at(end))){
					// 	nearbyNums.push_back(std::atoi(schema.at(lineNum).substr(end).c_str()));
					// }
					//auto right = check_vert(0, schema, lineNum, colNum);
					//for (const auto& elem : right) {
					//	nearbyNums.push_back(elem);
					//}
					//std::clog << "\n";

					// Check BELOW
					// if ((lineNum + 1) < totLines) {
					// 	for (int64_t i = begin; i < (end+1); i++) {
					// 		if (std::isdigit(schema.at(lineNum+1).at(i))) {
					// 			int64_t j = i;
					// 			while (std::isdigit(schema.at(lineNum+1).at(j))) {
					// 				--j;
					// 				if (j < 0) {
					// 					break;
					// 				}
					// 			}
					// 			bool consecutive = false;
					// 			if (i != begin && std::isdigit(schema.at(lineNum+1).at(i-1))) {
					// 				consecutive = true;
					// 			}
					// 			if (!consecutive) {
					// 				nearbyNums.push_back(std::atoi(schema.at(lineNum+1).substr(j+1).c_str()));
					// 			}
					// 		}
					// 		//std::clog << schema[lineNum+1][i];
					// 	}
					// 	//std::clog << "\n";
					// 	//std::clog << "linenum: " << lineNum << "\n";
					// }
					auto below = check_vert(1, schema, lineNum, colNum);
					for (const auto& elem : below) {
						nearbyNums.push_back(elem);
					}

					for (const auto& elem : nearbyNums) {
						//std::clog << elem << "\n";
					}
					//std::clog << "\n";
					//std::clog << "nearbybums size: " << nearbyNums.size() << "\n";
					//std::clog << "line number: " << lineNum+1 << "\n";
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

