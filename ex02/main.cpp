#include "PmergeMe.hpp"
#include <cstddef>
#include <exception>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <chrono>

std::size_t jocobsthalseq(std::size_t i) {
	// i += 0;
	return (((1 << i) - (i % 2 == 0 ? 1 : -1)) / 3);
}

std::size_t calculate(std::size_t len) {
	len -= 1;
	std::size_t seq = 0;
	std::size_t count = 0;

	for (std::size_t j = 1; j < len; ++j) {
		for (std::size_t i = 0; i < jocobsthalseq(j + 1); ++i) {
			if (len == count) return seq;
			seq += j;
			count++;
		}
	}
	return 0;
}

// int main(int argc, char *argv[]) {
int main() {

	// std::vector<int> input = {4, 5, 212, 42, 21, 2, 1, 40, 37};
	// std::vector<int> input = {4, 5, 212, 42, 61, 2, 1, 40};
	std::vector<int> input = {61, 33, 90, 28, 13, 37, 88, 69, 2, 26, 95, 81, 38, 75, 52, 15, 92, 42, 53, 84, 99, 48, 17, 67, 7, 58, 30, 20, 46, 72, 86};
	// std::vector<int> input = {61, 33, 90, 28, 13, 37, 88, 69, 2, 26, 95, 81, 38, 75, 52, 15, 92, 42, 53, 84, 99};
	std::size_t nbr_of_comparisons = 0;
	std::cout << "Before: ";
	for (int nbr : input) std::cout << nbr << " ";
	std::cout << std::endl;

	auto start = std::chrono::high_resolution_clock::now();
	// vec_sort(input);
	// vec_sort1(input);
	// vec_sort2(input);
	// vec_sort3(input);
	vec_prep(input, nbr_of_comparisons);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


	std::cout << "After: ";
	for (int nbr : input) std::cout << nbr << " ";
	std::cout << std::endl;

	std::cout << "Time to process a range of " << input.size() << " elements with std::vector : " << duration.count() << " μs" << std::endl;
	std::cout << "number of comparisons: " << nbr_of_comparisons << "(" << calculate(input.size()) << ")" <<  std::endl;
	// for ( int nbr : std::get<std::vector<int>>(flex_vec)) std::cout << nbr << " ";
	// std::cout << std::endl;
	// PmergeMe algo;
	// try {
	// 	algo.built_containers(argc, argv);
	// 	// algo.sort_pairs();
	// 	algo.mergeInsertion(0, argc - 2);
	// } catch (const std::exception& e) {
	// 	std::cout << e.what() << std::endl;
	// }
	// if ( argc == 1) {
	// 	std::cout << "please enter some positive integer values" << std::endl;
	// 	return 0;
	// }


	return 0;
}
