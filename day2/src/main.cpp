#include <array>
#include <cstddef>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>

#include "../include/header.hpp"

#define NUMBER_INDEX 5 

int main(int charc, char** argv){
	std::ifstream in("input.txt");
	std::string currLine;


	if (in.is_open()) {
		while (std::getline(in, currLine)){
			if(currLine.empty()){
				break;
			}
			Game currGame;
			setGameID(currLine, currGame);
			setGameRounds(currLine, currGame);
			//return 0;
		}
	}
	else{
		std::cerr << "Error: Failed to open file\n";
	}

	return EXIT_SUCCESS;
}

