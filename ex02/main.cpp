#include "PmergeMe.hpp"
#include <cstddef>
#include <exception>
#include <iostream>
#include <utility>
#include <vector>
#include <chrono>

// int main(int argc, char *argv[]) {
int main() {

	std::vector<int> input = {4, 5, 21, 2, 212, 42, 1, 40, 37};

	std::cout << "Before: ";
	for (int nbr : input) std::cout << nbr << " ";
	std::cout << std::endl;

	auto start = std::chrono::high_resolution_clock::now();
	// vec_sort(input);
	// vec_sort1(input);
	vec_sort2(input);
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


	std::cout << "After: ";
	for (int nbr : input) std::cout << nbr << " ";
	std::cout << std::endl;

	std::cout << "Time to process a range of " << input.size() << " elements with std::vector : " << duration.count() << " μs" << std::endl;
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
