#include "../include/day2.hpp"
#include <numeric>

namespace day2 {
	auto isNumeber = [](unsigned char c) {
		return std::isdigit(c);
	};

	std::vector<std::string> split_str(std::string_view string, const char* splitter){
		size_t pos = 0;
		size_t delim = 0;
		std::string delim_char(splitter);
		std::string token;
		std::vector<std::string> ret;
	
		while (delim != std::string::npos) {
			delim = string.find(delim_char, pos);
			token = string.substr(pos, delim - pos);
			ret.emplace_back(token);
			pos = delim + 1;
		}
		return ret;
	}
	
	void setGamePossibility(Game& game){
		for (const auto& elem : game.rounds) {
			if (elem.at(0) > COUNT_RED || elem.at(1) > COUNT_GREEN || elem.at(2) > COUNT_BLUE) {
				game.isPossible = false;
				break;
			}
			else {
				game.isPossible = true;
			}
		}
	}
	
	void parseGame(std::string_view line, Game& game){
		int red, green, blue;
		size_t colonIdx = line.find(":");
	
		game.gameId = std::atoi(line.substr(NUMBER_IDX, colonIdx - NUMBER_IDX).data());
	
		auto rounds = split_str(line, ":");
		rounds = split_str(rounds.at(1), ";");
	
		for (const auto& elem : rounds) {
			auto colours = split_str(elem, ",");
			for (const auto& cubes : colours) {
				int currCount = std::atoi(cubes.c_str());
	
				red = cubes.contains("red") ? currCount : red;
				green = cubes.contains("green") ? currCount : green;
				blue = cubes.contains("blue") ? currCount : blue;
			}
	
			game.rounds.push_back({red, green, blue});
			red = 0;
			green = 0;
			blue = 0;
		}
	}
	
	uint32_t partTwo(Game& game){
		int red = 0, green = 0, blue = 0;
		
		for (const auto& elem : game.rounds) {
			red = elem.at(0) > red ? elem.at(0) : red;
			green = elem.at(1) > green ? elem.at(1) : green;
			blue = elem.at(2) > blue ? elem.at(2) : blue;
		}
	
		int power =  red*green*blue;
		//std::cerr << "power:" << power << "\n";
		return power;
	}

	std::string part1(std::ifstream& input){
		std::string currLine;
		std::vector<int> possibleGameIDs;
		static uint32_t sum = 0;
	
		while (std::getline(input, currLine)){
			if(currLine.empty()){
				break;
			}
			Game currGame;
			parseGame(currLine, currGame);
	
			setGamePossibility(currGame);
	
			if (currGame.isPossible) {
				possibleGameIDs.push_back(currGame.gameId);	
			}
		}
		return std::to_string(std::accumulate(possibleGameIDs.begin(), possibleGameIDs.end(), 0));
	}

	std::string part2(std::ifstream& input){
		std::string currLine;
		static uint32_t sum = 0;
	
		while (std::getline(input, currLine)){
			if(currLine.empty()){
				break;
			}
			Game currGame;
			parseGame(currLine, currGame);
	
			sum += partTwo(currGame);
		}
		return std::to_string(sum);
	}

	Day day(2, &part1, &part2);
}

