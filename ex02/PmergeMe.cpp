#include "PmergeMe.hpp"
#include <algorithm>
#include <atomic>
#include <cstddef>
#include <cstdio>
#include <deque>
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


std::shared_ptr<PolyBase> PolyPair::getMax() const {
	return _max;
}

std::shared_ptr<PolyBase> PolyPair::getMin() const {
	return _min;
}

PolyNbr::PolyNbr(int nbr) : _nbr(nbr) {
	// std::cout << "PolyNbr constructor" << std::endl;
}

PolyNbr::PolyNbr() : _nbr(0) {
	// std::cout << "PolyNbr default constructor called" << std::endl;
}

PolyNbr::PolyNbr(const PolyNbr& other) : _nbr(other._nbr) {
	// std::cout << "Copy Constructor called" << std::endl;
}

PolyNbr& PolyNbr::operator=(const PolyNbr& other) {
	if (this != &other)
		return *this;
	return *this;
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

PolyPair::PolyPair() : _min(nullptr), _max(nullptr) {
	std::cout << "PolyPair default constructor" << std::endl;
}

PolyPair::PolyPair(const PolyPair& other) : _min(other._min), _max(other._max) {
	// std::cout << "PolyPair copy constructor called" << std::endl;
}

PolyPair& PolyPair::operator=(const PolyPair& other) {
	if (this != &other) {
		_min = getMin();
		_max = getMax();
	}
	// std::cout << "PolyPair Copy assignment operator" << std::endl;
	return *this;
}

PolyPair::~PolyPair() {
	// std::cout << "PolyPair Destructor" << std::endl;
}

int PolyPair::getNbr() const {
	return _max->getNbr();
}


// Jacobsthal Sequence converted to indexes starting with 0 2 4 10 20 42 84 170
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
	// #if DEBUG
	// 	std::cout << "size: " << size << std::endl;
	// #endif
	if (size == 1) return;

	std::vector<std::shared_ptr<PolyBase>> pair_vec;
	#if DEBUG
		std::cout << "init(↑↓):";
	#endif
	for (std::size_t i = 0; i + 1 < size; i += 2) {
			std::shared_ptr<PolyBase> new_pair = std::make_shared<PolyPair>((vec[i]) ,vec[i + 1]);
			#if DEBUG
				std::cout << "(↑" << std::dynamic_pointer_cast<PolyPair>(new_pair)->getMax()->getNbr()
					<< " ↓" << std::dynamic_pointer_cast<PolyPair>(new_pair)->getMin()->getNbr() << ")";
			#endif
			pair_vec.push_back(new_pair);
			compare++;
	}
	#if DEBUG
		std::cout << std::endl;
	#endif
	PmergeMe(pair_vec, compare);

	std::vector<std::shared_ptr<PolyBase>> main_chain;
	std::vector<std::shared_ptr<PolyBase>> pending_chain;
	// Min Element of smallest pair is always the smallest element
	// downcast to access derived class specific members that are not part of Base
	main_chain.push_back(std::dynamic_pointer_cast<PolyPair>(pair_vec[0])->getMin());
	for (std::size_t i = 0; i < pair_vec.size(); ++i) {
		main_chain.push_back(std::dynamic_pointer_cast<PolyPair>(pair_vec[i])->getMax());
		pending_chain.push_back(std::dynamic_pointer_cast<PolyPair>(pair_vec[i])->getMin());
		#if DEBUG
			std::cout << "(↑" << std::dynamic_pointer_cast<PolyPair>(pair_vec[i])->getMax()->getNbr();
			std::cout << " ↓" << std::dynamic_pointer_cast<PolyPair>(pair_vec[i])->getMin()->getNbr() << ")";
		#endif
	}
	#if DEBUG
		std::cout << std::endl;
	#endif
	if (size % 2 != 0) {
		// std::cout << "test remain: " << vec[size - 1]->getNbr() << std::endl;
		pending_chain.push_back(vec[size - 1]);
	}
	std::size_t end_condition;
	for (std::size_t i = 3; i < pending_chain.size() + 3; ++i) {
		end_condition = jSeq(i);
		if (end_condition >= pending_chain.size()) {
			break;
		}
	}
	#if DEBUG
		std::cout << "pending[" << pending_chain.size() << "] insert(idx): "
			<< std::dynamic_pointer_cast<PolyPair>(pair_vec[0])->getMin()->getNbr() << "(0)";
	#endif
	for (std::size_t j = 0; jSeq(j + 1) <= end_condition; ++j) {
		for (std::size_t i = jSeq(j + 1); i > jSeq(j); --i) {
			// if (pending_chain.size() == 1) break;
			if (i >= pending_chain.size()) {
				i = pending_chain.size() - 1;
				if (i <= jSeq(j))	break;
			}
			#if DEBUG
				std::cout << " " << pending_chain[i]->getNbr() << "(" << i << ")";
			#endif
			std::size_t idx = (1 << j) - 1;
			// std::cout << "idx " << idx << std::endl;
			if (idx > main_chain.size())
				idx = std::distance(main_chain.begin(), main_chain.end());
			// std::cout << "idx: " << idx << " j: " << j << " ";
			// auto it = std::lower_bound(main_chain.begin(), main_chain.begin () + idx, pending_chain[i], compare_helper);
			auto it = lower_bound_imp(main_chain.begin(), main_chain.begin() + idx, pending_chain[i], compare_helper, compare);
			// auto it = lower_bound_imp(main_chain.begin(), main_chain.end(), pending_chain[i], compare_helper, compare);
			main_chain.insert(it ,pending_chain[i]);
		}
	}
	#if DEBUG
		std::cout << "\n" << std::endl;
	#endif
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

void PmergeMeDeq(std::deque<std::shared_ptr<PolyBase>>& vec, std::size_t& compare) {
	std::size_t size = vec.size();
	if (size == 1) return;

	std::deque<std::shared_ptr<PolyBase>> pair_vec;

	for (std::size_t i = 0; i + 1 < size; i += 2) {
			std::shared_ptr<PolyBase> new_pair = std::make_shared<PolyPair>((vec[i]) ,vec[i + 1]);
			pair_vec.push_back(new_pair);
			compare++;
	}
	PmergeMeDeq(pair_vec, compare);

	std::deque<std::shared_ptr<PolyBase>> main_chain;
	std::deque<std::shared_ptr<PolyBase>> pending_chain;
	main_chain.push_back(std::dynamic_pointer_cast<PolyPair>(pair_vec[0])->getMin());
	for (std::size_t i = 0; i < pair_vec.size(); ++i) {
		main_chain.push_back(std::dynamic_pointer_cast<PolyPair>(pair_vec[i])->getMax());
		pending_chain.push_back(std::dynamic_pointer_cast<PolyPair>(pair_vec[i])->getMin());
	}
	if (size % 2 != 0) {
		pending_chain.push_back(vec[size - 1]);
	}
	std::size_t end_condition;
;
	for (std::size_t i = 3; i < pending_chain.size() + 3; ++i) {
		end_condition = jSeq(i);
		if (end_condition >= pending_chain.size()) {
			break;
		}
	}
	for (std::size_t j = 0; jSeq(j + 1) <= end_condition; ++j) {
		for (std::size_t i = jSeq(j + 1); i > jSeq(j); --i) {
			if (i >= pending_chain.size()) {
				i = pending_chain.size() - 1;
				if (i <= jSeq(j))	break;
			}
			std::size_t idx = (1 << j) - 1;
			if (idx > main_chain.size())
				idx = std::distance(main_chain.begin(), main_chain.end());
			auto it = lower_bound_imp(main_chain.begin(), main_chain.begin() + idx, pending_chain[i], compare_helper, compare);
			main_chain.insert(it ,pending_chain[i]);
		}
	}
	vec.swap(main_chain);
}



void deq_prep(std::deque<int>& vec, std::size_t& comparisons) {
	std::deque<std::shared_ptr<PolyBase>> Base;
	for (const auto& value : vec) {
		Base.push_back(std::make_shared<PolyNbr>(value));
	}
	PmergeMeDeq(Base, comparisons);
	for (std::size_t i = 0; i < Base.size(); ++i) {
		vec[i] = Base[i]->getNbr();
	}
}
