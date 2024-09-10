#include "../include/aoc-day.hpp"
#include <chrono>
#include <stdexcept>

Day::Day(int dayNum, std::string (*p1)(std::stringstream),std::string (*p2)(std::stringstream))
		: m_dayNum{dayNum}
		, m_part1{p1}
		, m_part2{p2}
{
	std::string path = "input/day" + std::to_string(m_dayNum);
	m_input.open(path);
	if (!m_input.is_open()) {
		// contructs a file in place (I think) ew
		throw std::runtime_error("Could not open file: " + path);
	}
}

void Day::run_day(){
	std::chrono::time_point<std::chrono::high_resolution_clock> begin;
	std::chrono::time_point<std::chrono::high_resolution_clock> end;


	begin = std::chrono::high_resolution_clock::now();
	run_part(1);
	end = std::chrono::high_resolution_clock::now();
	m_time1 = end - begin;

	begin = std::chrono::high_resolution_clock::now();
	run_part(2);
	end = std::chrono::high_resolution_clock::now();
	m_time2 = end - begin;
}

void Day::run_part(int part){
	std::chrono::time_point<std::chrono::high_resolution_clock> begin;
	std::chrono::time_point<std::chrono::high_resolution_clock> end;

	begin = std::chrono::high_resolution_clock::now();

	switch (part) {
		case 1:
			m_ans1 = (*m_part1)(m_input);
			end = std::chrono::high_resolution_clock::now();
			m_time1 = end - begin;
			break;
		case 2:
			m_ans2 = (*m_part2)(m_input);
			end = std::chrono::high_resolution_clock::now();
			m_time2 = end - begin;
			break;
		default:
			break;
	}
}

std::pair<std::string, std::string> Day::get_ans(){
	return std::make_pair(Day::get_ans_part(1), Day::get_ans_part(2));
}

std::string Day::get_ans_part(int part){
	switch (part) {
		case 1:
			return m_ans1;
			break;
		case 2:
			return m_ans2;
			break;
		default:
			break;
	}
}

void Day::set_part_func(std::string (*func)(std::ifstream&), int part){
	switch (part) {
		case 1:
			m_part1 = func;
			break;
		case 2:
			m_part2 = func;
			break;
		default:
			break;
	}
}

std::pair<std::chrono::duration<float>, std::chrono::duration<float>> Day::get_times(){
	return std::make_pair(get_time_part(1),get_time_part(2));
}

std::chrono::duration<float> Day::get_time_part(int part){
	switch (part) {
		case 1:
			return m_time1;
			break;
		case 2:
			return m_time2;
			break;
		default:
			break;
	}
}
