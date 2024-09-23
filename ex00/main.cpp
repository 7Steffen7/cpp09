#include <iostream>

#include <exception>
#include <map>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>

std::map<std::string, double> readDatabase(const std::string& database) {
	std::map<std::string, double> data;
	std::ifstream file(database);

	if (!file.is_open())
		throw std::invalid_argument("could not open database.");
	std::string line;
	if (!std::getline(file, line))
		throw std::invalid_argument("database is empty.");
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string date;
		double value;

		if (std::getline(ss, date, ',') && ss >> value)
			data[date] = value;
		else
			throw std::invalid_argument("invalid database");
	}
	return data;

}

int main(int argc, char *argv[]) {
	try {
		if (argc != 2) {
			throw std::invalid_argument("could not open file.");
		}
		std::map<std::string, double> database = readDatabase("data.csv");



	} catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}
