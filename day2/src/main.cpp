#include <iostream>
#include <cstdlib>
#include <fstream>
#include <numeric>

#include "../include/header.hpp"

int main(int charc, char** argv){
	std::ifstream in("input.txt");
	std::string currLine;
	std::vector<int> possibleGameIDs;

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
		setGamePossibility(currGame);

		if (currGame.isPossible) {
			possibleGameIDs.push_back(currGame.gameId);	
		}

		std::cout << "Possible game IDs:\n";
		for (const auto& elem : possibleGameIDs) {
			std::cout << elem << "\n";
		}
		std::cout << "ANSWER:" << std::accumulate(possibleGameIDs.begin(), possibleGameIDs.end(), 0) << "\n";
	}

	return EXIT_SUCCESS;
}

