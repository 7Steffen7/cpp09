#pragma once

#include <map>
#include <string>

class BitcoinExchange {
	public:
		BitcoinExchange(const std::string& input);
		~BitcoinExchange();
		void readDatabase();
		void searchDatabase();

	private:
		std::map<std::string, double> _database;
		const std::string _input_data;

		bool date_check(const std::string& date);
		bool value_check(double value);
		BitcoinExchange();
};
