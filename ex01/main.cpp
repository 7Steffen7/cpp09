#include "RPN.hpp"
#include <cstdlib>
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <sstream>

int main(int argc, char* argv[]) {
	try {
		if (argc != 2) {
			throw std::runtime_error("Error: Please enter your calculation");
		}
		RPN obj(argv[1]);
		obj.parsing();
		obj.print();

	} catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
