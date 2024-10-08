#include "PmergeMe.hpp"
#include <algorithm>
#include <cstddef>
#include <exception>
#include <iostream>
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

void PmergeMe::sort_pairs() {
	for (size_t i = 0; i < vec_container.size() - 1; i += 2) {
		if (vec_container[i] < vec_container[i + 1]) {
			std::swap(vec_container[i], vec_container[i + 1]);
		}
	}
	std::cout << "higher value of pair first:\n";
	for (const auto& element : vec_container) {
		std::cout  << element << " ";
	}
	std::cout << std::endl;
}


void PmergeMe::mergeInsertion(int start, int end) {
	// if (end - start <= 10) {
	// 	return;
	// }
	if (end - start <= 1)
		return;
	for (int i = start; i < end - 1; i += 2) {
		if (vec_container[i] < vec_container[i + 1])
			std::swap(vec_container[i], vec_container[i + 1]);
	}
	std::cout << "higher value of pair first:\n";
	for (const auto& element : vec_container) {
		std::cout  << element << " ";
	}
	// Split array into 2 parts
	int split_point = start + (start - end) / 2;
	mergeInsertion(start, split_point);
	std::cout << "sorted pairs:\n";
	for (const auto& element : vec_container) {
		std::cout  << element << " ";
	}
	std::cout << std::endl;

	// mergeInsertion(array, split_point + 1, end);

	// std::vector<int> temp;
	// for (int i = first_idx; i <= split_point; i += 2) {
	// 	if (i + 1 <= split_point) {
	// 		if (array[i] > array[i + 1]) {
	// 			std::swap(array[i], array[i + 1]);
	// 		}
	// 		temp.push_back(array[i]);
	// 	} else {
	// 		temp.push_back(array[i]);
	// 	}
	// }

	// merge(array, )
}
// void mergeInsertion(std::vector<int> array, int start, int end) {
// 	// if (end - start <= 10) {
// 	// 	return;
// 	// }
// 	if (end - start <= 1)
// 		return;

// 	// Split array into 2 parts
// 	int split_point = start + (start - end) / 2;
// 	mergeInsertion(array, start, split_point);
// 	std::cout << "sorted pairs:\n";
// 	for (const auto& element : array) {
// 		std::cout  << element << " ";
// 	}
// 	std::cout << std::endl;

// 	// mergeInsertion(array, split_point + 1, end);

// 	// std::vector<int> temp;
// 	// for (int i = first_idx; i <= split_point; i += 2) {
// 	// 	if (i + 1 <= split_point) {
// 	// 		if (array[i] > array[i + 1]) {
// 	// 			std::swap(array[i], array[i + 1]);
// 	// 		}
// 	// 		temp.push_back(array[i]);
// 	// 	} else {
// 	// 		temp.push_back(array[i]);
// 	// 	}
// 	// }

// 	// merge(array, )
// }
// void fordJohnson(std::variant<std::vector<int>,std::pair<int, int>>& flex_vec) {

void fordJohnson(std::variant<std::vector<int>, std::pair<std::vector<int>, std::vector<int>>>& flex_vec) {
	// check size of either std::vector<int> or std::pair<std::vector<int>, std::vector<int>>
	std::size_t size = std::visit([] (const auto& v) -> std::size_t {
	if constexpr (std::is_same_v<std::decay_t<decltype(v)>, std::vector<int>>) {
		return v.size();
	} else if constexpr (std::is_same_v<std::decay_t<decltype(v)>, std::pair<std::vector<int>, std::vector<int>>>) {
		return v.first.size();
	} else {
		throw std::runtime_error("Error");
	}
	}, flex_vec);
	std::cout << size << std::endl;
	if (size <= 1)
		return;

	std::pair<std::vector<int>, std::vector<int>> Pair;
	int unpaired = -1;
	// for (std::size_t i = 0; i + 1 < size; i += 2) {
	// 	Pair.emplace_back(flex_vec[i], flex_vec[i + 1]);
	// }
	std::visit([&](const auto& v) {
		if constexpr (std::is_same_v<std::decay_t<decltype(v)>, std::vector<int>>) {
			for (std::size_t i = 0; i + 1 < v.size(); i += 2) {
				Pair.first.push_back(v[i]);
				Pair.second.push_back(v[i + 1]);
				// Pair.emplace_back(v[i], v[i + 1]);
			}
			if (v.size() % 2 != 0) {
				unpaired = v.back();
			}
		} else if constexpr (std::is_same_v<std::decay_t<decltype(v)>, std::pair<std::vector<int>, std::vector<int>>>) {
			for (std::size_t i = 0; i + 1 < v.first.size(); ++i) {
				Pair.first.push_back(v.first[i]);
				Pair.second.push_back(v.first[i + 1]);
				// Pair.emplace_back(i, v.second);
			}
		}
	}, flex_vec);
	std::variant<std::vector<int>, std::pair<std::vector<int>, std::vector<int>>> rec = Pair;
	fordJohnson(rec);


	// std::size_t size = static_cast<std::vector<int>(flex_vec);
	// 	return;
	// std::vector<std::pair<int, int>> Pairs;
}
