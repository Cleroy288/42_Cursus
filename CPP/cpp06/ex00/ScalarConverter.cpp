#include "ScalarConverter.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <limits>

// Constructeurs et destructeur privés
ScalarConverter::ScalarConverter() {
    // Constructeur par défaut
}

ScalarConverter::ScalarConverter(const ScalarConverter &other) {
    // Constructeur de copie
	*this = other;

}

ScalarConverter::~ScalarConverter() {
    // Destructeur
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other) {
    // Opérateur d'assignation
	(void)other;
    return *this;
}

void ScalarConverter::convert(const std::string &str) {
    try {
        double num = std::stod(str);
        convertToChar(num);
        convertToInt(num);
        convertToFloat(num);
        convertToDouble(num);
    } catch (const std::exception &e) {
        std::cout << "Error: " << e.what() << '\n';
        std::cout << "char: impossible\nint: impossible\nfloat: impossible\ndouble: impossible\n";
    }
}

void ScalarConverter::convertToChar(double num) {
    if (num < std::numeric_limits<char>::min() || num > std::numeric_limits<char>::max() || !isPrintable(static_cast<int>(num))) {
        std::cout << "char: impossible" << std::endl;
    } else {
        char c = static_cast<char>(num);
        std::cout << "char: '" << c << "'" << std::endl;
    }
}

void ScalarConverter::convertToInt(double num) {
    if (std::isnan(num) || std::isinf(num) || num < std::numeric_limits<int>::min() || num > std::numeric_limits<int>::max()) {
        std::cout << "int: impossible" << std::endl;
    } else {
        int i = static_cast<int>(num);
        std::cout << "int: " << i << std::endl;
    }
}

void ScalarConverter::convertToFloat(double num) {
    float f = static_cast<float>(num);
    std::cout << "float: " << f << (f - static_cast<int>(f) == 0 ? ".0" : "") << "f" << std::endl;
}

void ScalarConverter::convertToDouble(double num) {
    std::cout << "double: " << num << (num - static_cast<int>(num) == 0 ? ".0" : "") << std::endl;
}

bool ScalarConverter::isPrintable(int c) {
    return c >= 32 && c <= 126;
}
