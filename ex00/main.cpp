#include "BitcoinExchange.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

#include <exception>
#include <map>
#include <stdexcept>
#include <string>
#include <fstream>
#include <sstream>
/*
map - elements in ascending order / alphabetically
unordered_map to avoid this behavior
*/



// bool exchange_check(double value) {

// 	if (value > 1000.0 || value < 0.0)
// 		return false;
// 	return true;
// }


int main(int argc, char *argv[]) {
	// (void)argv;
	try {
		if (argc != 2) {
			throw std::invalid_argument("could not open file.");
		}
		BitcoinExchange database(argv[1]);
		database.readDatabase();
		database.searchDatabase();



	} catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}
