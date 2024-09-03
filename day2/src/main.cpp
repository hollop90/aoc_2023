#include <cstdint>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <unordered_map>

#include "../include/header.hpp"

int main(){
	std::ifstream in("input.txt");
	std::string currLine;
	// std::vector<int> possibleGameIDs;
		static uint32_t sum = 0;

	if (!in.is_open()) {
		std::cerr << "Error: Failed to open file\n";
		return EXIT_FAILURE;
	}

	while (std::getline(in, currLine)){
		if(currLine.empty()){
			break;
		}
		Game currGame;
		parseGame(currLine, currGame);

		sum += partTwo(currGame);
		
		// setGamePossibility(currGame);

		// if (currGame.isPossible) {
		// 	possibleGameIDs.push_back(currGame.gameId);	
		// }

	}

	//std::cout << "ANSWER:" << std::accumulate(possibleGameIDs.begin(), possibleGameIDs.end(), 0) << "\n";
	std::cout << "ans:" << sum << std::endl;

	return EXIT_SUCCESS;
}

