#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#



BitcoinExchange::BitcoinExchange(const std::string& input) : _input_data(input) {
	std::cout << "BitcoinExchange string constructor called" << std::endl;
}

BitcoinExchange::~BitcoinExchange() {
	std::cout << "BitcoinExchange destructor called" << std::endl;
}

bool BitcoinExchange::date_check(const std::string& date) {

	// get current date
	auto now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::tm* timeinfo = std::localtime(&in_time_t);
	int current_year = timeinfo->tm_year + 1900;
	int current_month = timeinfo->tm_mon + 1;
	int current_day = timeinfo->tm_mday;
	// std::stringstream ss;
	// ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d");
	// std::cout << ss.str() << std::endl;
	// (void)date;

	std::stringstream ss(date);

	int year, month, day;
	char delimiter1, delimiter2;

	ss >> year >> delimiter1 >> month >> delimiter2 >> day;
	if (ss.fail() || delimiter1 != '-' || delimiter2 != '-')
		return false;
	if (year < 1900 || year > current_year)
		return false;
	if (month < 1 || month > 12)
		return false;
	if (month == 2) {
		if ((year % 4 == 0 && (day < 1 || day > 29))
			|| (year % 4 != 0 && (day < 1 || day > 28)))
			return false;
	}
	else if (((day < 1 || day > 31) && ((month % 2 == 1 && month < 8) || (month % 2 == 0 && month > 7)))
		|| ((day < 1 || day > 30) && ((month % 2 == 0 && month < 8) || (month % 2 == 1 && month > 7))))
		return false;
	else if (year > current_year || (year == current_year && month > current_month)
		|| (year == current_year && month == current_month && day > current_day))
		return false;

	return true;
}

void BitcoinExchange::readDatabase() {
	std::ifstream file("data.csv");

	if (!file.is_open())
		throw std::invalid_argument("could not open database.");
	std::string line;
	if (!std::getline(file, line))
		throw std::invalid_argument("database is empty.");
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string date;
		double value;

		if (std::getline(ss, date, ',') && ss >> value) {
			if (!date_check(date))
				throw std::invalid_argument("invalid database");
		_database[date] = value;
		}
		else
			throw std::invalid_argument("invalid database");
			// for (const auto& pair : data) {
			// 	std::cout << pair.first << " - " << pair.second << std::endl;
			// }
			// std::cout << "map size: " << data.size() << std::endl;
	}
}
