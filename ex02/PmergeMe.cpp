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

// void fordJohnson(std::vector<int> vec) {
// 	std::size_t size = vec.size();
// 	if (size <= 1) return;
// }

void fordJohnson1(std::vector<std::pair<int, int>>& vec) {
	std::size_t size = vec.size();
	if (size <= 1) return;
	int odd_leftover = -1;
	if (size % 2 != 0) {
		odd_leftover = vec[size - 1].first;
		vec.pop_back();
		size--;
	}

	std::vector<std::pair<int, int>> pair_vec;
	for (std::size_t i = 0; i + 1 < size; i += 2) {
		if (vec[i].first > vec[i + 1].first) {
			pair_vec.emplace_back(vec[i].first, vec[i + 1].first);
		} else {
			pair_vec.emplace_back(vec[i + 1].first, vec[i].first);
		}
	}
	fordJohnson1(pair_vec);
	std::vector<int> main_chain;
	std::vector<int> pending_chain;

	for (const auto& [first, second] : pair_vec) {
		main_chain.push_back(first);
		pending_chain.push_back(second);
	}

	if (odd_leftover != -1)
		pending_chain.push_back(odd_leftover);

	std::cout << "main chain: ";
	for (int nbr : main_chain) std::cout << nbr << " ";
	std::cout << std::endl;

	std::cout << "pending chain: ";
	for (int nbr : pending_chain) std::cout << nbr << " ";
	std::cout << std::endl;

	for (const int& element : pending_chain) {
		auto it = std::lower_bound(main_chain.begin(), main_chain.end(), element);
		main_chain.insert(it, element);
	}

	for (std::size_t i = 0; i < main_chain.size(); ++i) {
		vec[i].first = main_chain[i];
	}
}

void fordJohnson(std::pair<std::vector<int>, std::vector<int>>& double_vec) {
	std::size_t size = double_vec.first.size();
	if (size <= 1)
		return;

	std::pair<std::vector<int>, std::vector<int>> Pair;
	for (std::size_t i = 0; i + 1 < double_vec.first.size(); i += 2) {
		// debug
		// std::cout << double_vec.first[i] << " " << double_vec.first[i + 1] << " ";
		if (double_vec.first[i] > double_vec.first[i + 1]) {
			Pair.first.push_back(double_vec.first[i]);
			Pair.second.push_back(double_vec.first[i + 1]);
		} else {
			Pair.first.push_back(double_vec.first[i + 1]);
			Pair.second.push_back(double_vec.first[i]);
		}
	}
	//debug
	// std::cout << std::endl;
	int odd_leftover = -1;
	if (double_vec.first.size() % 2 != 0)
		odd_leftover = double_vec.first.back();
	fordJohnson(Pair);

	std::vector<int> main_chain = Pair.first;
	std::vector<int> pending_chain = Pair.second;
	if (odd_leftover != - 1) {
		pending_chain.push_back(odd_leftover);
	}
	std::cout << "pending chain: ";
	for (int nbr : pending_chain) std::cout << nbr << " ";
	std::cout << std::endl;

	// debug
	// std::cout << "main chain: ";
	// for (int num : main_chain) std::cout << num << " ";
	// std::cout << std::endl;

	// debug
	// std::cout << "pending chain: ";
	// for (int num : pending_chain) std::cout << num << " ";
	// std::cout << std::endl;

	for (const int& element : pending_chain) {
		auto it = std::lower_bound(main_chain.begin(), main_chain.end(), element);
		main_chain.insert(it, element);
	}
	// if (odd_leftover != -1) {
	// 	auto it = std::lower_bound(main_chain.begin(), main_chain.end(), odd_leftover);
	// 	main_chain.insert(it, odd_leftover);
	// }

	//debug
	// std::cout << "new main chain: ";
	// for (int num : main_chain) std::cout << num << " ";
	// std::cout << std::endl;

	double_vec.first = main_chain;
}

void vec_sort(std::vector<int>& input) {
	std::pair<std::vector<int>, std::vector<int>> double_vec;
	double_vec.first = input;
	fordJohnson(double_vec);
	input = double_vec.first;
}

void vec_sort1(std::vector<int> &input) {
	std::vector<std::pair<int, int>> pair_vec;

	for (const auto& value : input ) {
		pair_vec.emplace_back(value, 0);
	}
	fordJohnson1(pair_vec);
	for (std::size_t i = 0; i < input.size(); ++i) {
		input[i] = pair_vec[i].first;
	}
}
