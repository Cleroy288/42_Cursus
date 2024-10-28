#include "RPN.hpp"

void	printS(const std::string &string) {
	std::cout<<string<<std::endl;
}

void	PrintErr(const std::string &string) {
	std::cerr<<string<<std::endl;
}

bool 	isValidOperator(const std::string &token) {
	return token == "+" || token == "-" || token == "*" || token == "/";
}

bool isNumber(const std::string &token) {
    if (token.empty()) {
        return false;
    }
    
    for (std::string::const_iterator it = token.begin(); it != token.end(); ++it) {
        if (*it != '.' && !std::isdigit(*it)) {
            return false;
        }
    }
    
	try {
    	long num = std::stol(token);
    	if (num >= 10) {
        	return false;
    	}
	} catch(std::exception &e) {
		return false;
	}
    
    return true;
}

bool 	parsing(const std::string &argument) {
    std::istringstream iss(argument);
    std::string token;
    long long operandCount = 0;

    while (iss >> token) {
        if (isNumber(token)) {
            ++operandCount;
        } else if (isValidOperator(token)) {
            if (operandCount < 2) {
                PrintErr("Error: Expression in wrong format: " + argument);
                return false;
            }
            --operandCount; // Une opération consomme deux opérandes et en produit une
        } else {
            PrintErr("Error: Wrong token: " + token);
            return false;
        }
    }

    if (operandCount != 1) {
        PrintErr("Error: Final expression invalid or incomplete.");
        return false;
    }

    return true;
}

double	applyOperator(const std::string &op, double a, double b) {
	if (op == "+") {
		return a + b;
	}
	else if (op == "-") {
		return a - b;
	}
	else if (op == "*") {
		return a * b;
	}
	else if (op == "/") {
		if (b == 0)
			throw std::runtime_error("Division by zero");
		return a / b;
	}
	throw std::runtime_error("Invalid operator");
}

std::string FormatNumber(double value) {
    std::string str = std::to_string(value);

    // Vérify if value is int
    if (std::floor(value) == value) {
        // get away unuseful 0
        str.erase(str.find_last_not_of('0'), std::string::npos); // find last character who is not 0
        if (str.back() == '.') { // Vérify if the last char is à .
            str.pop_back(); // remove decimal point
        }
    }
    return str;
}

bool	executeRPN(const std::string &argument) {
	// tokenization 
	std::istringstream 	iss(argument);
	std::string 		token;
	// container
	std::stack<double>	stack;
	// operants 
	double 				a;
	double				b;
	double				result;

	while (iss >> token) {
		if (isNumber(token)) {
			stack.push(std::stod(token));
		}
		else if (isValidOperator(token)) {
			if (stack.size() < 2) {
				PrintErr("Error wrong format");
				return false;
			}
			a = stack.top();// take first elem
			stack.pop();// takeout first el
			b = stack.top(); // take new first el
			stack.pop(); // take new frist el
			result = applyOperator(token, b, a); // create result
			stack.push(result); // set restult as new el
 		}
		else {
			PrintErr("Error wrong token");
			return false;
		}
	}
	if (stack.size() == 1) {
    	printS("Result: " + FormatNumber(stack.top())); // Utilisez stack.top() avec des parenthèses
    	return true;
	}
	else {
		PrintErr("Error: final expression invalid or uncomplete");
		return false;
	}
}