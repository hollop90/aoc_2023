#ifndef UGO_AOC_2023
#define UGO_AOC_2023

#include <chrono>
#include <filesystem>
#include <fstream>
#include <string>

class Day{
private:
	// static member variables and functions
	// https://www.learncpp.com/cpp-tutorial/static-member-variables/
	static inline std::filesystem::path m_binPath;

	std::ifstream m_input;
	int m_dayNum;
	std::string m_ans1 {};
	std::string m_ans2 {};
	std::chrono::duration<float> m_time1 {};
	std::chrono::duration<float> m_time2 {};

	std::string (*m_part1)(std::ifstream& s);
	std::string (*m_part2)(std::ifstream& s);
public:
	Day() = delete;
	Day(int dayNum, std::string (*p1)(std::ifstream&), std::string (*p2)(std::ifstream&));
	~Day();

	int get_day_id();

	static void set_bin_path(std::filesystem::path path);

	// Run both or only one part
	void run_day();
	void run_part(int part);

	// Get both or only one ans
	std::pair<std::string, std::string> get_ans();
	std::string get_ans_part(int part);

	// Set both or one func pointer
	void set_func(std::string (*func1)(std::ifstream&), std::string (*func2)(std::ifstream&));
	void set_func_part(std::string (*func)(std::ifstream&), int part);

	// Get one or both run times
	std::pair<std::chrono::duration<float>, std::chrono::duration<float>> get_times();
	std::chrono::duration<float> get_time_part(int part);
};
#endif  // UGO_AOC_2023

