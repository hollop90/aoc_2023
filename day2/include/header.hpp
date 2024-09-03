#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <string_view>

#define NUMBER_IDX 5

typedef struct {
	int gameId;
	std::vector<std::array<int, 3>> rounds;
	bool  isPossible;

} Game;

auto isNumeber = [](unsigned char c) {
	return std::isdigit(c);
};

void setGameID(std::string_view line, Game& game){
	size_t colonIdx = line.find(":");
	game.gameId = std::atoi(line.substr(NUMBER_IDX, colonIdx - NUMBER_IDX).data());
}

std::vector<std::string> split_str(std::string_view string, const char* splitter){
	size_t pos = 0;
	size_t delim;

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

void setRoundColours(std::string_view line, Game& game){
	int red;
	int green;
	int blue;

	std::cerr << "Curr line:" << line << "\n";
	auto rounds = split_str(line, ":");
	rounds = split_str(rounds.at(1), ";");

	for (const auto& elem : rounds) {
		std::cerr << "Rounds:" << elem << "\n";
		auto colours = split_str(elem, ",");
		for (const auto& cubes : colours) {
			std::cerr << "Cubes:" << cubes << "\n";
			int currCount = std::atoi(cubes.c_str());

			red = cubes.contains("red") ? currCount : red;
			green = cubes.contains("green") ? currCount : green;
			blue = cubes.contains("blue") ? currCount : blue;
		}
			std::cout << "\n";
		game.rounds.push_back({red, green, blue});
		red = 0;
		green = 0;
		blue = 0;
	}

	for (const auto& elem : game.rounds) {
		std::cerr << "Round:" << elem.at(0) << " " << elem.at(1) << " " << elem.at(2) << "\n";
	}
}

void setGameRounds(std::string_view line, Game& game){
	setRoundColours(line, game);
}

