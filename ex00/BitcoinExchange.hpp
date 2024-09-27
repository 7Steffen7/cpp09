#pragma once

#include <map>
#include <string>

class BitcoinExchange {
	public:
		BitcoinExchange(const std::string& input);
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();
		void readDatabase();
		void searchDatabase();

	private:
		std::map<std::string, double> _database;
		std::string _input_data;

		bool date_check(const std::string& date);
		BitcoinExchange();
};
