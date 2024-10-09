#include "PmergeMe.hpp"
#include <exception>
#include <iostream>
#include <utility>
#include <vector>

// int main(int argc, char *argv[]) {
int main() {
	// using simpleVector = std::vector<int>;
	// using pairVector = std::vector<std::pair<int, int>>;
	// using flexVector = std::variant<simpleVector, pairVector>;
	// std::variant<std::vector<int>, std::vector<std::pair<int, int>>> flex;;
	std::vector<int> input = {4, 5, 21, 2, 212, 42, 1, 40, 37};
	// std::variant<std::vector<int>,std::pair<std::vector<int>, std::vector<int>>> flex_vec = input;
	std::pair<std::vector<int>, std::vector<int>> flex_vec;
	flex_vec.first = input;
	fordJohnson(flex_vec);

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
