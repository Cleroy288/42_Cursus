#include "Fixed.hpp"
#include <iostream>

// Implémentation du constructeur par défaut.
Fixed::Fixed() : fixedPointValue(0) {//si un objet fixed est crée et que il n'y à pas de valeur fourni ca valeur brute == 0
    std::cout << "Default constructor called" << std::endl;
}

// Implémentation du constructeur de copie.
Fixed::Fixed(const Fixed &src) {
    std::cout << "Copy constructor called" << std::endl;
    *this = src;  // Utilise l'opérateur d'affectation pour copier la valeur.
	//this->src == NOK, Car src est un paramètres de fonction et non de classe
}

// Implémentation du destructeur.
Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}

// Implémentation de l'opérateur d'affectation.
Fixed &Fixed::operator=(const Fixed &rhs) {//copie la valeur brute de l'objet source rhs et et le copie dans l'objet actuelle
    std::cout << "Copy assignment operator called" << std::endl;
    // Vérifie si l'objet actuel n'est pas le même que l'objet source.
    if (this != &rhs)
        this->fixedPointValue = rhs.getRawBits();
    return *this;
}

// Implémentation de la fonction pour obtenir la valeur brute.
int Fixed::getRawBits(void) const {//renvoi la valeur de FixedPointValue, elle renvoi la valeur brute stocké dans un objet
    std::cout << "getRawBits member function called" << std::endl;
    return this->fixedPointValue;
}

// Implémentation de la fonction pour définir la valeur brute.
void Fixed::setRawBits(int const raw) {//défini directement la valeur rbute de FixedPointValue
    this->fixedPointValue = raw;
}