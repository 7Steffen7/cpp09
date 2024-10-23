#pragma once

#include <algorithm>
#include <deque>
#include <memory>
#include <utility>
#include <vector>
#include <variant>

#define DEBUG false


class PolyBase {
	public:
		virtual ~PolyBase() = default;
		virtual int getNbr() const = 0;
};

class PolyPair : public PolyBase {
	public:
		PolyPair(const std::shared_ptr<PolyBase>& first, const std::shared_ptr<PolyBase>& second);
		PolyPair(const PolyPair& other);
		PolyPair& operator=(const PolyPair& other);
		~PolyPair();
		int getNbr() const override;
		std::shared_ptr<PolyBase> getMax() const;
		std::shared_ptr<PolyBase> getMin() const;
	private:
		PolyPair();
		std::shared_ptr<PolyBase> _min;
		std::shared_ptr<PolyBase> _max;
};

class PolyNbr : public PolyBase{
	public:
		explicit PolyNbr(int nbr);
		PolyNbr(const PolyNbr& other);
		~PolyNbr();
		int getNbr() const override;
	private:
		PolyNbr();
		PolyNbr& operator=(const PolyNbr& other);
		const int _nbr;
};

void vec_prep(std::vector<int>& input, std::size_t& comparisons);
void deq_prep(std::deque<int>& input, std::size_t& comparisons);
