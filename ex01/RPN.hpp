#pragma once

#include <sstream>
#include <stack>

class RPN {
	public:
		RPN(const char* input);
		~RPN();
		void parsing();
		void print() const;
	private:
		std::stack<int> _buffer;
		const std::string _input;
		int calculate(int first, int second, const std::string& operators);
};
