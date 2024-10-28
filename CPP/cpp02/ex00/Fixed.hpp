#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed {
private:
    // Membre pour stocker la valeur du nombre en virgule fixe.
    int fixedPointValue;
    static const int fractionalBits = 8;

public:
    // Déclaration des constructeurs et destructeur.
    Fixed();  // Constructeur par défaut.
    Fixed(const Fixed &src);  // Constructeur de copie.
    ~Fixed();  // Destructeur.

    // Surcharge de l'opérateur d'affectation.
    Fixed &operator=(const Fixed &rhs);

    // Fonctions pour obtenir et définir la valeur brute.
    int getRawBits(void) const;
    void setRawBits(int const raw);
};

#endif
