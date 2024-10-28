#include "PmergeMe.hpp"

void	PrintS(const std::string &str) {
	std::cout<<str<<std::endl;
}

void	PrintErr(const std::string &str) {
	std::cerr<<str<<std::endl;
}

bool	isPositiveInteger(const std::string &str) {
	long	value;
	
	if (str.empty()) {
		return false;
	}
	try {
		value = std::stol(str);
		if (value < std::numeric_limits<int>::min() || value > std::numeric_limits<int>::max())
			return false;
		for (unsigned long i = 0; i < str.size(); i++) {
			if (!std::isdigit(str[i]))
				return false;

		}
	}
	catch (const std::exception &e) {
		return false;
	}
	return true;
}

bool	parsing(const std::deque<std::string> &args) {
	for (unsigned long i = 0; i < args.size(); i++) {
		if (!isPositiveInteger(args[i])) {
			return false;
		}
	}
	return true;
}

