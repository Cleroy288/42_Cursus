#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

// Classe représentant un nombre à virgule fixe
class Fixed {
private:
    int fixedPointValue; // Valeur brute (entiére) du nombre à virgule fixe
    static const int fractionalBits = 8; // Nombre de bits pour la partie fractionnaire

public:
    // Constructeurs et destructeur
    Fixed();  // Constructeur par défaut
    Fixed(const int intValue);  // Constructeur à partir d'un entier
    Fixed(const float floatValue);  // Constructeur à partir d'un flottant
    Fixed(const Fixed &src);  // Constructeur de copie
    ~Fixed();  // Destructeur

    // Opérateur d'affectation
    Fixed &operator=(const Fixed &rhs);

    // Méthodes pour obtenir et définir la valeur brute
    int getRawBits(void) const;
    void setRawBits(int const raw);

    // Conversion en flottant et entier
    float toFloat(void) const;
    int toInt(void) const;

    // Surcharge des opérateurs de comparaison
    bool operator>(const Fixed &rhs) const;
    bool operator<(const Fixed &rhs) const;
    bool operator>=(const Fixed &rhs) const;
    bool operator<=(const Fixed &rhs) const;
    bool operator==(const Fixed &rhs) const;
    bool operator!=(const Fixed &rhs) const;

    // Surcharge des opérateurs arithmétiques
    Fixed operator+(const Fixed &rhs) const;
    Fixed operator-(const Fixed &rhs) const;
    Fixed operator*(const Fixed &rhs) const;
    Fixed operator/(const Fixed &rhs) const;


    // Opérateurs d'incrémentation et de décrémentation
    Fixed &operator++();   // Pré-incrémentation
    Fixed operator++(int); // Post-incrémentation
    Fixed &operator--();   // Pré-décrémentation
    Fixed operator--(int); // Post-décrémentation

    // Méthodes statiques pour trouver le minimum et le maximum

    static const Fixed &min(const Fixed &a, const Fixed &b);
	static const Fixed &max(const Fixed &a, const Fixed &b);
	static Fixed &min(Fixed &a, Fixed &b);
	static Fixed &max(Fixed &a, Fixed &b);

};

// Surcharge de l'opérateur de flux pour l'affichage
std::ostream &operator<<(std::ostream &os, const Fixed &fixed);

#endif
