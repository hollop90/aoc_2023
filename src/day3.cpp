#include "../include/day3.hpp"

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

	std::string part1(std::ifstream& in){
		std::vector<int> validPartNums;

		std::vector<std::string> a;

		std::string line;
		while (std::getline(in, line)) {
			if (line.empty()) {
				break;
			}
			a.push_back(line);
			//std::cerr << line << "\n";
		}

		for (size_t i = 0; i < a.size(); i++) {
			//std::cerr << a.at(i) << "\n";
			for (size_t lineIdx = 0; lineIdx < a.at(i).length(); lineIdx++) {
				if (std::isdigit(a.at(i).at(lineIdx))) {
					// It's ugly, it's inefficient, but it works and that's all that matters for now
					int partNum = std::atoi(a.at(i).substr(lineIdx, std::string::npos).c_str());	

					std::stringstream ss;
					ss << partNum;

					std::string s;
					ss >> s;
					int partNumLen = s.length();

					//std::cerr << "num:" << s << "\n";
					//std::cerr << "len:" << partNumLen << "\n";
					//std::cerr << "\n";

					const size_t begin = (lineIdx-1) == SIZE_MAX ? 0 : lineIdx-1;
					const size_t end = (lineIdx+partNumLen) > a.size()-1 ? a.size()-1 : lineIdx+partNumLen;

					bool found = false;

					// above
					if ((i-1) != SIZE_MAX) {
						for (size_t symIdx = begin; symIdx < end+1; symIdx++) {
							if (a.at(i-1).at(symIdx) != '.' && !std::isdigit(a.at(i-1).at(symIdx))) {
								//std::cerr << "VALID\n";
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
						//std::cerr << "VALID\n";
								found = true;
						validPartNums.push_back(partNum);	
					}	
					if (found) {
						lineIdx += partNumLen;
						continue;
					}

					if (a.at(i).at(end) != '.' && !std::isdigit(a.at(i).at(end))) {
						//std::cerr << "VALID\n";
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
								//std::cerr << "VALID\n";
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
		//std::cerr << "total nums:" << validPartNums.size() << "\n";
		for (const auto& elem : validPartNums) {
			//std::cerr << "validnum:" << elem << "\n";
		}
		int sum = std::accumulate(validPartNums.begin(), validPartNums.end(), 0);

		std::cout << "ans:" << sum << "\n";
		return std::to_string(sum);
	}

	std::string part2(std::ifstream& input){
		return "";
	}

	Day day(3, &part1, &part2);
}


