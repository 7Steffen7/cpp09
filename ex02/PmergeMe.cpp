#include "PmergeMe.hpp"
#include <algorithm>
#include <cstddef>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

PmergeMe::PmergeMe(int argc, char *argv[]) {
	try {
		built_containers(argc, argv);
	} catch (const std::exception& e) {
		throw;
	}
	std::cout << "String array constructor called" << std::endl;
}

PmergeMe::~PmergeMe() {
	std::cout << "Destructor called" << std::endl;
}

void PmergeMe::built_containers(int argc, char *argv[]){
	if (argc == 1 || argv[1][0] == '\0')
		throw std::invalid_argument("plese enter some positive integers");
	// check .reserve(argc - 1) for vector later on
	for (int i = 1; i < argc; ++i) {
		try {
			int value = std::stoi(argv[i]);
			if (value < 0)
				throw std::invalid_argument(std::to_string(i) + ": Number must be a positve integer");
			vec_container.push_back(value);
			deq_container.push_back(value);
		} catch (const std::exception& e) {
			throw;
		}
	}
	for (const auto& element : vec_container) {
		std::cout << "vector: " << element << std::endl;
	}
	for (const auto& element : deq_container) {
		std::cout << "deque: " << element << std::endl;
	}
}

// void PmergeMe::look_for_duplicates(const std::vector<int>& vec) {
// 	std::vector<int> vec_copy = vec;

// 	std::sort(vec_copy.begin(), vec_copy.end());
// 	if (std::adjacent_find(vec_copy.begin(), vec_copy.end()) == vec_copy.end())
// 		throw std::invalid_argument("Duplicate found");
// }
