#include <cctype>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main(int argc, char** argv){
	std::vector<int> validPartNums;
	std::filesystem::path path = std::filesystem::path(argv[0]).parent_path().append("input.txt");
	std::ifstream in(path);

	if (!in.is_open()) {
		std::cerr << "Failed to open file: " << path << "\n";
		return EXIT_FAILURE;
	}

	std::vector<std::string> a;

	std::string line;
	while (std::getline(in, line)) {
		if (line.empty()) {
			break;
		}
		a.push_back(line);
	}

	for (size_t rowIdx = 0; rowIdx < a.size(); rowIdx++) {
		for (size_t charIdx = 0; charIdx < a.at(rowIdx).length(); charIdx++) {
			if (std::isdigit(a.at(rowIdx).at(charIdx))) {
				// It's ugly, it's inefficient, but it works and that's all that matters for now
				int partNum = std::atoi(a.at(rowIdx).substr(charIdx, std::string::npos).c_str());	

				std::stringstream ss;
				ss << partNum;

				std::string s;
				ss >> s;
				int partNumLen = s.length();

				const size_t begin = (charIdx-1) == SIZE_MAX ? 0 : charIdx-1;
				const size_t end = (charIdx+partNumLen) > a.size()-1 ? a.size()-1 : charIdx+partNumLen;

				bool found = false;

				// above
				if ((rowIdx-1) != SIZE_MAX) {
					for (size_t symIdx = begin; symIdx < end+1; symIdx++) {
						if (a.at(rowIdx-1).at(symIdx) != '.' && !std::isdigit(a.at(rowIdx-1).at(symIdx))) {
							found = true;
							validPartNums.push_back(partNum);	
							break;
						}	
					}
					if (found) {
						charIdx += partNumLen;
						continue;
					}
				}

				// inline
				if (a.at(rowIdx).at(begin) != '.' && !std::isdigit(a.at(rowIdx).at(begin))) {
					found = true;
					validPartNums.push_back(partNum);	
				}	
				if (found) {
					charIdx += partNumLen;
					continue;
				}

				if (a.at(rowIdx).at(end) != '.' && !std::isdigit(a.at(rowIdx).at(end))) {
					found = true;
					validPartNums.push_back(partNum);	
				}	
				if (found) {
					charIdx += partNumLen;
					continue;
				}

				// below
				if ((rowIdx+1) < a.at(rowIdx).size()) {
					for (size_t symIdx = begin; symIdx < end+1; symIdx++) {
						if (a.at(rowIdx+1).at(symIdx) != '.' && !std::isdigit(a.at(rowIdx+1).at(symIdx))) {
							found = true;
							validPartNums.push_back(partNum);	
							break;
						}	
					}
					if (found) {
						charIdx += partNumLen;
						continue;
					}
				}
				charIdx += partNumLen;
			}
		}
	}
	for (auto elem : validPartNums) {
		std::cout << elem << "\n";	
	}
	std::cout << "ans:" << std::accumulate(validPartNums.begin(), validPartNums.end(), 0) << "\n";
}

