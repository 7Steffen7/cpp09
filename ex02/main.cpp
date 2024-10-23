#include "PmergeMe.hpp"
#include <algorithm>
#include <cctype>
#include <cstddef>
#include <deque>
#include <exception>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>
#include <chrono>

// Jacobthal sequence: 0, 1, 1, 3, 5, 11, 21, 43, 85, 171 ...
std::size_t jocobsthalseq(std::size_t i) {
	return (((1 << i) - (i % 2 == 0 ? 1 : -1)) / 3);
}

std::size_t calculate(std::size_t len) {
	len -= 1;
	std::size_t seq = 0;
	std::size_t count = 0;

	if (len == 1) return 1;
	if (len == 2) return 3;
	for (std::size_t j = 1; j < len; ++j) {
		for (std::size_t i = 0; i < jocobsthalseq(j + 1); ++i) {
			if (len == count) return seq;
			seq += j;
			count++;
		}
	}
	return 0;
}

template<typename T>
void check_fun(std::size_t nbr_of_comparison, const T& input) {
	static_assert(
		std::is_same<T, std::vector<int>>::value ||
		std::is_same<T, std::deque<int>>::value,
		"Container must be either std::vector<int> or std::deque<int>"
	);
	std::string type;
	if (std::is_same<T, std::vector<int>>::value) {
		type = "Vector: ";
	} else {
		type = "Deque: ";
	} size_t expected_max_nbr_of_comparison = calculate(input.size());
	if (std::is_sorted(input.begin(), input.end())) {
		std::cout << "\033[32m" << type << "numbers sorted / " << "\033[0m";
	} else {
		std::cout << "\033[31m" << type << "numbers not sorted / " << "\033[0m";
	} if (nbr_of_comparison <= expected_max_nbr_of_comparison) {
		std::cout << "\033[32m" << nbr_of_comparison << "(" << expected_max_nbr_of_comparison << ")" << "comparisons" << "\033[0m" <<  std::endl;
	} else {
		std::cout << "\033[31m" << nbr_of_comparison << "(" << expected_max_nbr_of_comparison << ")" << "comparisons" << "\033[0m" <<  std::endl;
	}
}

template<typename T>
void input_parsing(int argc, char *argv[], T& array) {
	static_assert(
		std::is_same<T, std::vector<int>>::value ||
		std::is_same<T, std::deque<int>>::value,
		"Container must be either std::vector<int> or std::deque<int>"
	);
	if (argc == 1) {
		throw std::runtime_error("Error: Please enter a positive integer sequence");
	} for (int i = 1; i < argc; ++i) {
		std::string str_nbr(argv[i]);
		if (str_nbr.empty()) {
			throw std::runtime_error("Error: Please enter a positive integer sequence");
		} for (char c : str_nbr) {
			if (!std::isdigit(c)) {
				throw std::runtime_error("Error: Please enter a positive integer sequence");
			}
		} try {
			long nbr = stol(str_nbr);
			if (nbr < 0 || nbr > std::numeric_limits<int>::max()) {
				throw std::runtime_error("Error: Please enter a positive integer sequence");
			} array.push_back(static_cast<int>(nbr));
		} catch (const std::out_of_range&) {
			throw std::runtime_error("Error: Please enter a positive integer sequence");
		} catch (const std::runtime_error&) {
			throw std::runtime_error("Error: Please enter a positive integer sequence");
		}
	}
}

// create random numbers
// ./PmergeMe `jot -r 3000 1 100000 | tr '\n' ' '`
int main(int argc, char *argv[]) {

	std::vector<int> vec_input;
	std::deque<int> deq_input;
	std::size_t nbr_of_comparisons = 0;
	std::size_t nbr_of_comparisons_deq = 0;

	try {
		input_parsing(argc, argv, vec_input);
		std::copy(vec_input.begin(), vec_input.end(), std::back_inserter(deq_input));
	} catch (const std::runtime_error& e) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	std::cout << "Before: ";
	for (int nbr : vec_input) std::cout << nbr << " ";
	std::cout << std::endl;
	auto start = std::chrono::high_resolution_clock::now();
	vec_prep(vec_input, nbr_of_comparisons);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

	start = std::chrono::high_resolution_clock::now();
	deq_prep(deq_input, nbr_of_comparisons_deq);
	end = std::chrono::high_resolution_clock::now();
	auto duration_deq = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


	std::cout << "After: ";
	for (int nbr : vec_input) std::cout << nbr << " ";
	std::cout << std::endl;

	std::cout << "Time to process a range of " << vec_input.size() << " elements with std::vector : " << duration.count() << " μs" << std::endl;
	std::cout << "Time to process a range of " << deq_input.size() << " elements with std::deque : " << duration_deq.count() << " μs" << std::endl;
	check_fun(nbr_of_comparisons, vec_input);
	check_fun(nbr_of_comparisons_deq, deq_input);
	return 0;
}
