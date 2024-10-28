#include "Fixed.hpp"
#include <iostream>

/*

Donc qu'est ce que c'est que la valeur brute ?! 
	valeur brute == représentation nombre à virgule avec valeur fixe.
		stocké dans FixedPointValues, getRawBits et setRawBits permet de récupérer et de définir cette valeur brute. 
			L'opérateur d'affectation permet de copier cette valeur d'un objet à un autre.

		DANS SE CODE CI ON TRAVAILLE DIRECTEMENT AVEC LES VALEURS BRUTES ON NE CONVERTI RIEN 
			ON à juste des méthodes pour obtenir (getRawBits) et définir (setRawBits) de tel valeurs.


*/

// Point d'entrée principal du programme.
int main(void) {
    // Crée un objet "a" de type Fixed en utilisant le constructeur par défaut.
    Fixed a;

    // Crée un objet "b" en copiant l'objet "a" avec le constructeur de copie.
    Fixed b(a);

    // Crée un objet "c" en utilisant le constructeur par défaut.
    Fixed c;

    // Attribue la valeur de "b" à "c" en utilisant l'opérateur d'affectation.
    c = b;

    // Affiche la valeur brute de chaque objet.
    std::cout << a.getRawBits() << std::endl;
    std::cout << b.getRawBits() << std::endl;
    std::cout << c.getRawBits() << std::endl;
    return 0;
}
