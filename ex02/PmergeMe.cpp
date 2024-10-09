#include "PmergeMe.hpp"
#include <algorithm>
#include <cstddef>
#include <exception>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

PmergeMe::PmergeMe() {
	std::cout << "Default constructor called" << std::endl;
}

PmergeMe::~PmergeMe() {
	std::cout << "Destructor called" << std::endl;
}

void PmergeMe::built_containers(int argc, char *argv[]){
	if (argc == 1 || argv[1][0] == '\0')
		throw std::invalid_argument("please enter some positive integers");
	// check .reserve(argc - 1) for vector later on
	for (int i = 1; i < argc; ++i) {
		try {
			int value = std::stoi(argv[i]);
			if (value < 0)
				throw std::invalid_argument(std::to_string(i) + ": Number must be a positve integer");
			vec_container.push_back(value);
			// add deque later !
			// deq_container.push_back(value);
		} catch (const std::exception& e) {
			throw;
		}
	}

	std::cout << "initial state:\n";
	for (const auto& element : vec_container) {
		std::cout  << element << " ";
	}
	std::cout << std::endl;
	// for (const auto& element : deq_container) {
	// 	std::cout << "deque: " << element << std::endl;
	// }
}

// void PmergeMe::look_for_duplicates(const std::vector<int>& vec) {
// 	std::vector<int> vec_copy = vec;

// 	std::sort(vec_copy.begin(), vec_copy.end());
// 	if (std::adjacent_find(vec_copy.begin(), vec_copy.end()) == vec_copy.end())
// 		throw std::invalid_argument("Duplicate found");
// }


void fordJohnson(std::pair<std::vector<int>, std::vector<int>>& double_vec) {
	size_t size = double_vec.first.size();
	if (size <= 1)
		return;

	std::pair<std::vector<int>, std::vector<int>> Pair;
	for (std::size_t i = 0; i + 1 < double_vec.first.size(); i += 2) {
		std::cout << double_vec.first[i] << " " << double_vec.first[i + 1] << " ";
		if (double_vec.first[i] > double_vec.first[i + 1]) {
			Pair.first.push_back(double_vec.first[i]);
			Pair.second.push_back(double_vec.first[i + 1]);
		} else {
			Pair.first.push_back(double_vec.first[i + 1]);
			Pair.second.push_back(double_vec.first[i]);
		}
	}
	int odd_leftover = -1;
	if (double_vec.first.size() % 2 != 0)
		odd_leftover = double_vec.first.back();
	std::cout << std::endl;
	fordJohnson(Pair);

	std::vector<int> main_chain = Pair.first;
	std::vector<int> pending_chain = Pair.second;

	std::cout << "main chain: ";
	for (int num : main_chain) std::cout << num << " ";
	std::cout << std::endl;

	std::cout << "pending chain: ";
	for (int num : pending_chain) std::cout << num << " ";
	std::cout << std::endl;

	for (const int& element : pending_chain) {
		auto it = std::lower_bound(main_chain.begin(), main_chain.end(), element);
		main_chain.insert(it, element);
	}
	if (odd_leftover != -1) {
		auto it = std::lower_bound(main_chain.begin(), main_chain.end(), odd_leftover);
		main_chain.insert(it, odd_leftover);
	}
	std::cout << "new main chain: ";
	for (int num : main_chain) std::cout << num << " ";
	std::cout << std::endl;

	double_vec.first = main_chain;
}
