#ifndef SCALARCONVERTER_HPP
#define SCALARCONVERTER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <limits>

class ScalarConverter {
public:
    static void convert(const std::string &str); // Méthode statique pour la conversion

private:
	// in private because ::  this class must not be instanciable by users
    ScalarConverter(); // Constructeur par défaut privé
    ScalarConverter(const ScalarConverter &other); // Constructeur 
    ~ScalarConverter(); // Destructeur 
    ScalarConverter &operator=(const ScalarConverter &other);

    // Méthodes auxiliaires pour gérer la conversion
    static void convertToChar(double num);
    static void convertToInt(double num);
    static void convertToFloat(double num);
    static void convertToDouble(double num);

    // Méthode pour déterminer si un caractère est imprimable
    static bool isPrintable(int c);
};

#endif
