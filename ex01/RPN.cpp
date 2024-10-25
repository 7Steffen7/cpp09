#include "RPN.hpp"
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

RPN::RPN(const char* input) : _input(std::string(input)) {
	// std::cout << "Default constructor called" << std::endl;
}

RPN::RPN() : _input(nullptr) {
	// std::cout << "Default Constructor" << std::endl;
}

RPN::RPN(const RPN& other) : _input(other._input) {
	// std::cout << "Copy constructor" << std::endl;
}

RPN::~RPN() {
	// std::cout << "Destructor called" << std::endl;
}

RPN& RPN::operator=(const RPN& other) {
	if (this != & other) return *this;
	return *this;
}
// void RPN::calculate() {

// };

bool isOperator(const std::string& token) {
	return token == "+" || token == "-" || token == "*" || token == "/";
}

long RPN::calculate(long first, long second, const std::string& operators) {
	switch(operators[0]) {
		case '+':
			return first + second;
		case '-':
			return first - second;
		case '*':
			return first * second;
		case '/':
			if (second == 0) throw std::runtime_error("Error");
			return first / second;
		default:
			throw std::runtime_error("Error");
	}
}

void RPN::parsing() {
	std::istringstream iss(_input);
	std::string token;
	while(iss >> token) {
		if (isOperator(token)) {
			if (_buffer.size() < 2) {
				throw std::runtime_error("Error");
			}
			long sec = _buffer.top();
			_buffer.pop();
			long fir = _buffer.top();
			_buffer.pop();
			_buffer.push(calculate(fir, sec, token));
		} else {
			try {
				long num = stol(token);
				if (num >= 0 && num <= 9) {
					_buffer.push(num);
				} else {
					throw std::runtime_error("Error");
				}
			} catch (const std::invalid_argument&) {
				throw std::runtime_error("Error");
			}
		}
	}
	if (_buffer.size() != 1) {
		throw std::runtime_error("Error");
	}
}

void RPN::print() const {
	std::cout << _buffer.top() << std::endl;
}
