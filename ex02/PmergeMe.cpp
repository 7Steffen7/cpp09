#include "PmergeMe.hpp"
#include <algorithm>
#include <atomic>
#include <cstddef>
#include <cstdio>
#include <exception>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>


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

std::shared_ptr<PolyBase> PolyPair::getMax() const {
	return _max;
}

std::shared_ptr<PolyBase> PolyPair::getMin() const {
	return _min;
}

PolyNbr::PolyNbr(int nbr) : _nbr(nbr) {
	// std::cout << "PolyNbr constructor" << std::endl;
}

PolyNbr::~PolyNbr() {
	// std::cout << "PolyNbr destructor" << std::endl;
}

int PolyNbr::getNbr() const {
	return _nbr;
}

// std::move to transfer ownership
PolyPair::PolyPair(const std::shared_ptr<PolyBase>& first, const std::shared_ptr<PolyBase>& second) {
	if (first->getNbr() > second->getNbr()) {
		_max = std::move(first);
		_min = std::move(second);
	} else {
		_max = std::move(second);
		_min = std::move(first);
	}
	// std::cout << "PolyPair constructor" << std::endl;
}


PolyPair::~PolyPair() {
	// std::cout << "PolyPair Destructor" << std::endl;
}

int PolyPair::getNbr() const {
	return _max->getNbr();
}

/*
a = max of pair;
b = min of pair;
a1, a2 ascending order
b1, b2
b1, a1, a2 = insert b1 -
isert b2 - is alwats smaller then a2
*/

// Jacobsthal Sequence converted to indeces starting with 0 2 4 10 20 42 84 170
std::size_t jSeq(std::size_t i) {
	return (((1 << i) - (i % 2 == 0 ? 1 : -1)) / 3) - 1;
}

auto compare_helper (const std::shared_ptr<PolyBase>& a, const std::shared_ptr<PolyBase>& b) {
		return a->getNbr() < b->getNbr();
	};

template<class ForwardIterator, class T, class Compare>
ForwardIterator lower_bound_imp(ForwardIterator first, ForwardIterator last, const T& val, Compare comp, std::size_t& counter) {
	ForwardIterator it;
	typename std::iterator_traits<ForwardIterator>::difference_type count, step;
	count = std::distance(first, last);
	while (count > 0) {
		it = first;
		step = count / 2;
		std::advance(it, step);
		// if(*it < val) {
		counter++;
		if (comp(*it, val)) {
			first = ++it;
			count -= step + 1;
		} else {
			count = step;
		}
	}
	return first;
}

void PmergeMe(std::vector<std::shared_ptr<PolyBase>>& vec, std::size_t& compare) {
	std::size_t size = vec.size();
	// std::cout << "size: " << size << std::endl;
	if (size <= 1) return;

	std::vector<std::shared_ptr<PolyBase>> pair_vec;

	// std::cout << "init(↑↓):";
	for (std::size_t i = 0; i + 1 < size; i += 2) {
			std::shared_ptr<PolyBase> new_pair = std::make_shared<PolyPair>((vec[i]) ,vec[i + 1]);
			// std::cout << "(↑" << std::dynamic_pointer_cast<PolyPair>(new_pair)->getMax()->getNbr()
			// 		<< " ↓" << std::dynamic_pointer_cast<PolyPair>(new_pair)->getMin()->getNbr() << ")";
			pair_vec.push_back(new_pair);
			compare++;
	}
	// std::cout << std::endl;
	PmergeMe(pair_vec, compare);

	std::vector<std::shared_ptr<PolyBase>> main_chain;
	std::vector<std::shared_ptr<PolyBase>> pending_chain;
	// Min Element of smallest pair is always the smallest element
	// downcast to access derived class specific members that are not part of Base
	main_chain.push_back(std::dynamic_pointer_cast<PolyPair>(pair_vec[0])->getMin());
	for (std::size_t i = 0; i < pair_vec.size(); ++i) {
		main_chain.push_back(std::dynamic_pointer_cast<PolyPair>(pair_vec[i])->getMax());
		pending_chain.push_back(std::dynamic_pointer_cast<PolyPair>(pair_vec[i])->getMin());
		// std::cout << "(↑" << std::dynamic_pointer_cast<PolyPair>(pair_vec[i])->getMax()->getNbr();
		// std::cout << " ↓" << std::dynamic_pointer_cast<PolyPair>(pair_vec[i])->getMin()->getNbr() << ")";
	}
	// std::cout << std::endl;
	if (size % 2 != 0) {
		// std::cout << "test remain: " << vec[size - 1]->getNbr() << std::endl;
		pending_chain.push_back(vec[size - 1]);
	}
	// auto compare_helper = [](const std::shared_ptr<PolyBase>& a, const std::shared_ptr<PolyBase>& b) {
	// 	return a->getNbr() < b->getNbr();
	// };
	// for (std::size_t i = pending_chain.size() - 1; i > 0 ; --i) {
	// 	auto it = std::lower_bound(main_chain.begin(), main_chain.end(), pending_chain[i], compare_helper);
	// 	main_chain.insert(it ,pending_chain[i]);
	// }
	std::size_t end_condition;
	// std::cout << "pen size: " << pending_chain.size() << std::endl;
;
	for (std::size_t i = 3; i < pending_chain.size() + 3; ++i) {
		// end_condition = jacobs[i];
		end_condition = jSeq(i);
		// std::cout << "end_con: " << end_condition << " ";
		if (end_condition >= pending_chain.size()) {
			break;
		}
	}
	// std::cout << std::endl;
	// std::cout << "end con: " << end_condition << std::endl;
	for (std::size_t j = 0; jSeq(j + 1) <= end_condition; ++j) {
		for (std::size_t i = jSeq(j + 1); i > jSeq(j); --i) {
			// if (pending_chain.size() == 1) break;
			if (i >= pending_chain.size()) {
				i = pending_chain.size() - 1;
				if (i <= jSeq(j))	break;
			}
			// std::cout << "pending size: " << pending_chain.size() << " nbr: " << pending_chain[i]->getNbr() << "(" << i << ")" <<  std::endl;
			std::size_t idx = (1 << j) - 2;
			// std::cout << "idx: " << idx << " j: " << j << " ";
			// auto it = std::lower_bound(main_chain.begin(), main_chain.begin () + idx, pending_chain[i], compare_helper);
			auto it = lower_bound_imp(main_chain.begin(), main_chain.begin() + idx, pending_chain[i], compare_helper, compare);
			// auto it = lower_bound_imp(main_chain.begin(), main_chain.end(), pending_chain[i], compare_helper, compare);
			main_chain.insert(it ,pending_chain[i]);
		}
	}

	// std::cout << "main chain:  ";
	// for (std::size_t i = 0; i < main_chain.size(); ++i) {
	// 	std::cout  << main_chain[i]->getNbr() << " ";
	// }
	// std::cout << std::endl;
	//exchange contents of vectors
	vec.swap(main_chain);
}

void vec_prep(std::vector<int>& vec, std::size_t& comparisons) {
	std::vector<std::shared_ptr<PolyBase>> Base;
	Base.reserve(vec.size());
	for (const auto& value : vec) {
		Base.push_back(std::make_shared<PolyNbr>(value));
	}
	PmergeMe(Base, comparisons);
	for (std::size_t i = 0; i < Base.size(); ++i) {
		vec[i] = Base[i]->getNbr();
	}
}
