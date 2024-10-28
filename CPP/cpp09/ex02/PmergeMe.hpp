#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <deque>
#include <sstream>
#include <string>
#include <cctype>
#include <vector>
#include <iterator>
#include <list>



void	PrintS(const std::string &str);
void	PrintErr(const std::string &str);
bool	isPositiveInteger(const std::string &str);
bool	parsing(const std::deque<std::string> &args);

#endif