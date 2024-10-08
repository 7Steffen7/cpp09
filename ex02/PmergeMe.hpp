#pragma once

#include <deque>
#include <vector>
#include <variant>



// using simpleVector = std::vector<int>;
// using pairVector = std::vector<std::pair<int, int>>;
// using flexVector = std::variant<simpleVector, pairVector>;

class PmergeMe {
public:
	PmergeMe();
	~PmergeMe();

	void built_containers(int argc, char *argv[]);
	void sort_pairs();
	void mergeInsertion(int start, int end);
	// void look_for_duplicates(const std::vector<int>& vec);

private:
	std::vector<int> vec_container;
	// std::deque<int> deq_container;
};

void fordJohnson(std::variant<std::vector<int>,std::pair<std::vector<int>, std::vector<int>>>& flex_vec);
