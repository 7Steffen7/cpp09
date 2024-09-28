// #include "RPN.hpp"
#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <sstream>

/*
parsing:
- seperate by space
- max amount of numbers == 10
- if string numberic convert to int - std::stoi
- always have to start with 2 numbers than operator, num, operator, num - everything else invalid
- stacksize should always be between 1 or 2
- when enconter an opertor (stacksize must be 2) pop both numbers out and do operation





*/


int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "User input missing" << std::endl;
		return 0;
	}
	// std::string input(argv[1]);
	std::istringstream iss(argv[1]);
	std::string word;
	std::stack<int> buffer;

	while (iss >> word) {
		try {
			int temp = std::stoi(word);
			if (buffer.size() <= 2)
				buffer.push(temp);
			else
				throw std::out_of_range("notation order invalid");
		} catch (const std::invalid_argument& e) {
			int	first_nbr;
			int second_nbr;


			second_nbr = buffer.top();
			buffer.pop();
			first_nbr = buffer.top();
			buffer.pop();
			switch (word[0]) {
				case '+':
					buffer.push(first_nbr + second_nbr);
					break;
				case '-':
					buffer.push(first_nbr - second_nbr);
					break;
				case '*':
					buffer.push(first_nbr * second_nbr);
					break;
				case '/':
					buffer.push(first_nbr / second_nbr);
					break;
				default:
					throw std::invalid_argument("Error");
			}
		} catch (const std::out_of_range& e) {
			std::cout << e.what() << std::endl;
			return 1;
		}
	}
	std::cout << buffer.top() << std::endl;

	return 0;
}
