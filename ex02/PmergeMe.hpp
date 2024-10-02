#pragma once

#include <deque>
#include <vector>



class PmergeMe {
public:
	PmergeMe(int argc, char *argv[]);
	~PmergeMe();

	void built_containers(int argc, char *argv[]);
	// void look_for_duplicates(const std::vector<int>& vec);

private:
	PmergeMe();
	std::vector<int> vec_container;
	std::deque<int> deq_container;
};
