#pragma once

#include <algorithm>
#include <deque>
#include <memory>
#include <utility>
#include <vector>
#include <variant>



// using simpleVector = std::vector<int>;
// using pairVector = std::vector<std::pair<int, int>>;
// using flexVector = std::variant<simpleVector, pairVector>;

// class PmergeMe {
// public:
// 	PmergeMe();
// 	~PmergeMe();

// 	void built_containers(int argc, char *argv[]);
// 	void sort_pairs();
// 	void mergeInsertion(int start, int end);
// 	// void look_for_duplicates(const std::vector<int>& vec);

// private:
// 	std::vector<int> vec_container;
// 	// std::deque<int> deq_container;
// };


class PolyBase {
	public:
		virtual ~PolyBase() = default;
		virtual int getNbr() const = 0;
};

class PolyPair : public PolyBase {
	public:
		// PolyPair(PolyBase* first, PolyBase* second);
		PolyPair(const std::shared_ptr<PolyBase>& first, const std::shared_ptr<PolyBase>& second);
		~PolyPair();
		int getNbr() const override;
		std::shared_ptr<PolyBase> getMax() const;
		std::shared_ptr<PolyBase> getMin() const;
	private:
		std::shared_ptr<PolyBase> _min;
		std::shared_ptr<PolyBase> _max;
};

class PolyNbr : public PolyBase{
	public:
		explicit PolyNbr(int nbr);
		~PolyNbr();
		int getNbr() const override;
	private:
		const int _nbr;
};


// void fordJohnson(std::variant<std::vector<int>,std::pair<std::vector<int>, std::vector<int>>>& flex_vec);
void fordJohnson(std::pair<std::vector<int>, std::vector<int>>& double_vec);
void vec_sort(std::vector<int>& input);
void vec_sort1(std::vector<int>& input);

// template<typename T>
void vec_sort2(std::vector<int>& input);
void vec_sort3(std::vector<int>& input);
void vec_prep(std::vector<int>& input, std::size_t& comparisons);
