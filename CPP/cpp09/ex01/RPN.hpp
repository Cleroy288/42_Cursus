#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <stack>
#include <stdexcept>
#include <cmath>


void	printS(const std::string &string);
void	PrintErr(const std::string &string);
bool 	isValidOperator(const std::string &token);
bool 	isNumber(const std::string &token);
bool 	parsing(const std::string &argument);
bool	executeRPN(const std::string &argument);

#endif