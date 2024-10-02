#include "PmergeMe.hpp"
#include <exception>
#include <iostream>

int main(int argc, char *argv[]) {
	PmergeMe algo;
	try {
		algo.built_containers(argc, argv);
		algo.sort_pairs();
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	// if ( argc == 1) {
	// 	std::cout << "please enter some positive integer values" << std::endl;
	// 	return 0;
	// }


	return 0;
}
