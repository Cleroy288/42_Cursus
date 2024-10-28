#include "HumanB.hpp"  // Inclut la définition de la classe HumanB.
#include <iostream>

// Constructeur de HumanB. Initialise le nom avec la valeur fournie et met l'arme à nullptr, 
// indiquant que HumanB n'a pas encore d'arme attribuée.
HumanB::HumanB(std::string name) : name(name), weapon(nullptr) {}

// Méthode permettant de définir l'arme de HumanB. Cette méthode prend une référence à une arme 
// et stocke son adresse. Cette approche permet à HumanB d'obtenir une arme à un moment après sa construction.
void HumanB::setWeapon(Weapon &newWeapon) {
    weapon = &newWeapon;  // Stocke l'adresse de l'objet weapon, pas une copie de l'objet.
}

// Méthode représentant une attaque par HumanB. Si HumanB a une arme (i.e., weapon n'est pas nullptr), 
// il attaque avec. Sinon, le programme indique que HumanB n'a pas d'arme.
void HumanB::attack() const {
    if (weapon) {
        // weapon est un pointeur, donc nous utilisons l'opérateur -> pour accéder à ses méthodes/membres.
        std::cout << name << " attacks with their " << weapon->getType() << std::endl;
    } else {
        // Ce bloc s'exécute si HumanB n'a pas d'arme (i.e., lorsque weapon est nullptr).
        std::cout << name << " has no weapon" << std::endl;
    }
}

