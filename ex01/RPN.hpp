#pragma once

#include <sstream>
#include <stack>

class RPN {
	public:
		RPN(const char* input);
		RPN(const RPN& other);
		~RPN();
		void parsing();
		void print() const;
	private:
		RPN();
		RPN& operator=(const RPN& other);
		std::stack<int> _buffer;
		const std::string _input;
		int calculate(int first, int second, const std::string& operators);
};
