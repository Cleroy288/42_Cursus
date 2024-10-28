#include "Fixed.hpp"
#include <cmath>

/// --- ===== CONSTRUCTEURS ET DESTRUCTEURS --- ===== ////

//constructeur par défault 
Fixed::Fixed() : fixedPointValue(0) {
}

//constructeur sur base d'un int 
Fixed::Fixed(const int intValue) {
    fixedPointValue = intValue << fractionalBits;
}

//constructeur sur base d'un floate
Fixed::Fixed(const float floatValue) {
    fixedPointValue = roundf(floatValue * (1 << fractionalBits));
}

//constructeur de copie
Fixed::Fixed(const Fixed &src) {
    *this = src;
}

Fixed::~Fixed() {
}

//////// --- ==== Les 6 opérateur de comparaison : >, <, >=, <=, == et !=. --- ==== ///////

// Définition de l'opérateur < (comparaison)
bool Fixed::operator<(const Fixed &rhs) const {
    return this->fixedPointValue < rhs.fixedPointValue;
}

bool Fixed::operator>(const Fixed &rhs) const {
    return this->fixedPointValue > rhs.fixedPointValue;
}

bool Fixed::operator>=(const Fixed &rhs) const {
    return !(*this < rhs);
}

bool Fixed::operator<=(const Fixed &rhs) const {
    return !(*this > rhs);
}

bool Fixed::operator==(const Fixed &rhs) const {
    return this->fixedPointValue == rhs.fixedPointValue;
}

bool Fixed::operator!=(const Fixed &rhs) const {
    return !(*this == rhs);
}


///// --- ==== • Les 4 opérateurs de arithmétiques : +, -, *, et /  ==== ----////

// Définition de l'opérateur * (multiplication) 
Fixed Fixed::operator*(const Fixed &rhs) const {
    Fixed result;
    result.fixedPointValue = (this->fixedPointValue * rhs.fixedPointValue) >> fractionalBits;
    return result;
}

Fixed Fixed::operator+(const Fixed &rhs) const {
    Fixed res;
    res.fixedPointValue = this->fixedPointValue + rhs.fixedPointValue;
    return res;
}

Fixed Fixed::operator-(const Fixed &rhs) const {
    Fixed res;
    res.fixedPointValue = this->fixedPointValue - rhs.fixedPointValue;
    return res;
}

Fixed Fixed::operator/(const Fixed &rhs) const {
    if (rhs.fixedPointValue == 0) {
        throw std::runtime_error("Division by zero");
    }
    Fixed res;
    res.fixedPointValue = (this->fixedPointValue << fractionalBits) / rhs.fixedPointValue;
    return res;
}

Fixed &Fixed::operator=(const Fixed &rhs) {
    this->fixedPointValue = rhs.getRawBits();
    return *this;
}


///// --- ==== • Les 4 opérateurs d’incrémentation et de décrémentation (pré-incrémentation et  --- === ////
////  --- ==== post-incrémentation, pré-décrémentation et post-décrémentation) qui diminueront  --- === ////
////  --- ==== la valeur du nombre à virgule fixe d’unité  tel que 1 +  > 1.                 --- === ////


Fixed &Fixed::operator++() {
    fixedPointValue++;
    return *this;
}

Fixed &Fixed::operator--() {
    fixedPointValue--;
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed tmp(*this);    // copy
    ++fixedPointValue;  // Increment
    return tmp;          // Return copy
}

Fixed Fixed::operator--(int) {
    Fixed tmp(*this);    //copy
    --fixedPointValue;  // Decrement
    return tmp;          // Return copy
}


/// --- ==== Ajoutez à votre classe ces quatre fonctions membres publiques surchargées :  --- === ////


const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
	if (a < b)
		return (a);
	else
		return (b);
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
	if (a > b)
		return (a);
	else
		return (b);
}

Fixed &Fixed::min(Fixed &a, Fixed &b) {
	if (a < b)
		return (a);
	else
		return (b);
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
	if (a > b)
		return (a);
	else
		return (b);
}


// Surcharge de l'opérateur de flux pour l'affichage
std::ostream &operator<<(std::ostream &os, const Fixed &fixed) {
    os << fixed.toFloat();
    return os;
}

// Définition de getRawBits (méthode pour obtenir l avaleur brute)
int Fixed::getRawBits() const {
    return this->fixedPointValue;
}

// Définition de toFloat
float Fixed::toFloat() const {
    return static_cast<float>(fixedPointValue) / (1 << fractionalBits);
}

int Fixed::toInt(void) const {
    return fixedPointValue >> fractionalBits;
}



