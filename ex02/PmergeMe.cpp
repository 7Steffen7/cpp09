#include "PmergeMe.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdio>
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

// void sort_pairs(std::vector<std::pair<int, int>> vec_pair, std::vector<int> main_chain, std::vector<int> pending_chain) {

// }

// void vec_sort2(std::vector<int>& input) {
// 	std::vector<std::pair<int, int>> vec_pair;
// 	std::vector<int> main_chain;
// 	std::vector<int> pending_chain;
// 	for (std::size_t i = 0; i + 1; i += 2) {
// 		if (input[i] > input [i + 1]) {
// 			vec_pair.emplace_back(input[i], input[i + 1]);
// 		} else {
// 			vec_pair.emplace_back(input[i + 1], input[i]);
// 		}
// 		sort_pairs(vec_pair, main_chain, pending_chain);
// 	}
// }

template<typename T>
void print_containers(std::vector<std::pair<T*, T*>> container) {
	// std::cout << "test " << std::endl;
	for (const auto& [first, second] : container) {
		if (first && second)
			std::cout << "(" << *first << ", " << *second << ")";
		else
			std::cout << "(" << *first << ", " << "nullptr" << ")";
	}
	std::cout << std::endl;
}

// template<typename int>
void fordJohnson2(std::vector<std::pair<int*, int*>>& p_vec) {

	std::size_t size = p_vec.size();
	std::cout << "size: " << size << std::endl;

	if (size <= 1) return;

	print_containers(p_vec);
	// int odd_nbrs = -1;
	// std::pair<int*,int*>* odd_nbrs = nullptr;
	// if (size % 2) {

	// 	odd_nbrs = &p_vec.back();
	// 	p_vec.pop_back();
	// 	--size;
	// }
	std::vector<std::pair<int*, int*>> pair_vec;
	for (std::size_t i = 0; i + 1 < size; i += 2) {
		if (*p_vec[i].first > *p_vec[i + 1].first) {
			pair_vec.emplace_back(p_vec[i].first, p_vec[i + 1].first);
		} else {
			pair_vec.emplace_back(p_vec[i + 1].first, p_vec[i].first);
		}
	}
	fordJohnson2(pair_vec);
	// std::vector<std::pair<int*, int*>> main_chain;
	// std::vector<std::pair<int*, int*>> pending_chain;
	std::vector<int*> main_chain;
	std::vector<int*> pending_chain;

	for (const auto& [first, second] : pair_vec) {
		main_chain.push_back(first);
		pending_chain.push_back(second);
		// main_chain.emplace_back(first, nullptr);
		// pending_chain.emplace_back(second, nullptr);
	}

	// if (odd_nbrs) {
	// 	pending_chain.push_back(odd_nbrs->first);
	// 	pending_chain.push_back(odd_nbrs->second);
	// 	odd_nbrs = nullptr;
	// }
	std::cout << "main_chain_size: " << main_chain.size() << std::endl;
	if (main_chain.size() == 2) {
		std::swap(main_chain[0], main_chain[1]);
		std::swap(pending_chain[0], pending_chain[1]);
	}

	std::cout << "main chain: ";
	// print_containers(main_chain);
	for (int* nbr : main_chain) std::cout << *nbr << " ";
	std::cout << std::endl;

	std::cout << "pending chain: ";
	// print_containers(pending_chain);
	for (int* nbr : pending_chain) std::cout << *nbr << " ";
	std::cout << std::endl;

	// std::cout << "main_chain size: " << main_chain.size() << std::endl;

	// for (int* element : pending_chain) {
	// 	auto it = std::lower_bound(main_chain.begin(), main_chain.end(),
	// 			element, [](const int* a, const int* b) {return *a < *b; } );
	// 	main_chain.insert(it, element);
	// }
	p_vec.clear();

	// p_ve

	// std::cout << "main_chain_size: " << main_chain.size() << std::endl;
	for (std::size_t i = 0; i < main_chain.size(); i++) {
		// if (i + 1 < main_chain.size()) {
			// p_vec.emplace_back(main_chain[i], main_chain[i + 1]);
		// } else {
			p_vec.emplace_back(main_chain[i], pending_chain[i]);
		// 	// p_vec.emplace_back(main_chain[i], main_chain[i]);
		// }
		// p_vec.push_back(main_chain[i]);
	}
}

// template<typename int>
void vec_sort2(std::vector<int>& input) {
	std::vector<std::pair<int*, int*>> p_vec;
	// std::vector<int*> p_vec;
	for (int& nbr : input) {
		p_vec.emplace_back(&nbr, nullptr);
	}
	fordJohnson2(p_vec);
}
// 4 5 212 42 21 2 1 40 37;
// (4 5)* (212 42)* (21 2)* (1 40)* (37)*;
// ((4 5)* (212 42)*)p

// std::vector<std::pair<int*, int*>*> pair_vec;



void printPairs(const std::vector<std::pair<int*, int*>*>& pairs, const std::string& message) {
	std::cout << message << std::endl;
	for (std::size_t i = 0; i < pairs.size(); ++i) {
		std::cout << "Pair " << i << " at " << pairs[i] << ": ("
			<< *pairs[i]->first << " at " << static_cast<void*>(pairs[i]->first) << ", ";
		if (pairs[i]->second)
			std::cout << *pairs[i]->second  << " at " << static_cast<void*>(pairs[i]->second);
		else
			std::cout << "nullptr";
		std::cout << ")\n";
	}
	std::cout	<< std::endl;
}

void fjay(std::vector<std::pair<int*, int*>*>& input) {
	std::size_t size = input.size();
	// std::cout << "size: " << size << std::endl;

	if (size <= 1) return;
	printPairs(input, "sorting pairs");

	std::pair<int*, int*>* odd_leftover;
	if (input.size() % 2 != 0) {
		odd_leftover = input.back();
		input.pop_back();
	}

	std::vector<std::pair<int*, int*>*> new_pair;
	for (std::size_t i =  0; i < input.size(); i += 2) {
		int* first = input[i]->first;
		int* last = (i + 1 < input.size()) ? input[i + 1]->first : nullptr;
		new_pair.push_back(new std::pair<int*, int*>(first, last));
	}

	for (std::size_t i = 0; i < new_pair.size(); ++i) {
		if (new_pair[i]->second && *new_pair[i]->first < *new_pair[i]->second) {
			std::swap(new_pair[i]->first, new_pair[i]->second);
			std::swap(input[i * 2]->first, input[i * 2 + 1]->first);
			std::swap(input[i * 2]->second, input[i * 2 + 1]->second);
		}
	}
	fjay(new_pair);
	printPairs(input, "input after recursion");
	printPairs(new_pair, "new_pair after recursion");
}

void vec_sort3(std::vector<int> &input) {
	std::vector<std::pair<int*, int*>*> p_vec;

	for (size_t i = 0; i < input.size(); ++i) {
		p_vec.push_back(new std::pair<int*, int*>(&input[i], nullptr));
	}
	fjay(p_vec);
}
