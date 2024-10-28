#include "Fixed.hpp"

/***********************************************************/
//constructeur par défault, met fixed point value à Zéro
Fixed::Fixed() : fixedPointValue(0) {
    std::cout << "Default constructor called" << std::endl;
}
/*
    Un constructeur prenant un entier constant en paramètre et qui convertit celuici en virgule fixe.
    Le nombre de bits de la partie fractionnaire est initialisé à 8comme dans l’exercice 00.
*/
Fixed::Fixed(const int intValue) {
    std::cout << "Int constructor called" << std::endl;
    fixedPointValue = intValue << fractionalBits;
}

/*
    Un constructeur prenant un flottant constant en paramètre et qui convertit
    celui-ci en virgule fixe. Le nombre de bits de la partie fractionnaire est initialisé à
    8 comme dans l’exercice 00.
*/
Fixed::Fixed(const float floatValue) {
    std::cout << "Float constructor called" << std::endl;
    fixedPointValue = roundf(floatValue * (1 << fractionalBits));
}

//constructeur de copie
Fixed::Fixed(const Fixed &src) {
    std::cout << "Copy constructor called" << std::endl;
    *this = src;
}

/******************/
Fixed::~Fixed() {
    std::cout << "Destructor called" << std::endl;
}
/*********************************************************/
Fixed &Fixed::operator=(const Fixed &rhs) {
    std::cout << "Copy assignment operator called" << std::endl;
    this->fixedPointValue = rhs.getRawBits();
    return *this;
}

int Fixed::getRawBits(void) const {
    return fixedPointValue;
}

void Fixed::setRawBits(int const raw) {
    fixedPointValue = raw;
}

/**********************************************************/

/*
    Une fonction membre float toFloat( void ) const;
    qui convertit la valeur en virgule fixe en nombre à virgule flottante.
*/
float Fixed::toFloat(void) const {
    return (float)fixedPointValue / (1 << fractionalBits);
}
/*
    Une fonction membre int toInt( void ) const;
    qui convertit la valeur en virgule fixe en nombre entier.
*/
int Fixed::toInt(void) const {
    return fixedPointValue >> fractionalBits;
}
/************************************************************/
/*
    Une surcharge de l’opérateur d’insertion («) qui insère une représentation en virgule
    flottante du nombre à virgule fixe dans le flux de sortie (objet output stream)
    passé en paramètre.
*/
std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
    os << fixed.toFloat();
    return os;
}
