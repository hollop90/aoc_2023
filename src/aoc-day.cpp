#include "../include/aoc-day.hpp"
#include <chrono>
#include <filesystem>
#include <stdexcept>
#include <iostream>

Day::Day(int dayNum, std::string (*p1)(std::ifstream&),std::string (*p2)(std::ifstream&))
		: m_dayNum{dayNum}
		, m_part1{p1}
		, m_part2{p2}
{
}

void Day::set_bin_path(std::filesystem::path path){
	m_binPath = std::filesystem::canonical(path);
	//std::cout << m_binPath << "\n";
}

void Day::run_day(){
	run_part(1);
	run_part(2);
}

int Day::get_day_id(){
	return m_dayNum;
}

void Day::run_part(int part){
	if (!m_input.is_open()) {
		std::filesystem::path path = m_binPath / ("day" + std::to_string(m_dayNum) + ".txt");
		m_input.open(path);
		if(!m_input.is_open()){
			// contructs a file in place (I think) ew
			throw std::runtime_error("Could not open file: " + path.string());
		}
	}

	m_input.clear();
	m_input.seekg(0);

	std::chrono::time_point<std::chrono::high_resolution_clock> begin;
	std::chrono::time_point<std::chrono::high_resolution_clock> end;

	switch (part) {
		case 1:
			begin = std::chrono::high_resolution_clock::now();
			m_ans1 = (*m_part1)(m_input);
			end = std::chrono::high_resolution_clock::now();
			m_time1 = end - begin;
			break;
		case 2:
			begin = std::chrono::high_resolution_clock::now();
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
			return "";
			break;
	}
}

void Day::set_func(std::string (*func1)(std::ifstream&), std::string (*func2)(std::ifstream&)){
	m_part1 = func1;
	m_part2 = func2;
}

void Day::set_func_part(std::string (*func)(std::ifstream&), int part){
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
			return std::chrono::duration<float>(0);
			break;
	}
}

Day::~Day(){
	m_input.close();
}
