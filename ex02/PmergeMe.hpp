#pragma once

#include <deque>
#include <vector>



class PmergeMe {
public:
	PmergeMe();
	~PmergeMe();

	void built_containers(int argc, char *argv[]);
	void sort_pairs();
	// void look_for_duplicates(const std::vector<int>& vec);

private:
	std::vector<int> vec_container;
	// std::deque<int> deq_container;
};
