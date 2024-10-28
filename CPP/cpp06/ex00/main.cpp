#include "ScalarConverter.hpp"
#include <iostream>

int main(int argc, char **argv) {

	if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            std::cout << "============================" << std::endl;
            std::cout << "Testing with literal: " << argv[i] << std::endl;
            ScalarConverter::convert(argv[i]);
            std::cout << std::endl;
        }
    }
	else {
    	// Test avec différents types de littéraux
    	std::string tests[] = {
        	"0", "42", "-42", // int tests
        	"0.0f", "-4.2f", "4.2f", // float tests
        	"0.0", "-4.2", "4.2", // double tests
        	"a", "Z", // char tests
        	"-inff", "+inff", "nanf", // float pseudo literals
        	"-inf", "+inf", "nan", // double pseudo literals
        	"2147483647", "-2147483648", // int limit cases
        	"2.5", "Hello", "42.42f42" // invalid inputs
    	};

		for (size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i) {
    		const std::string& test = tests[i];
	    	std::cout << "============================" << std::endl;
        	std::cout << "Testing with literal: " << test << std::endl;
        	ScalarConverter::convert(test);
        	std::cout << std::endl;
    	}
	}
    return 0;
}
