#ifndef HUMANB_HPP
#define HUMANB_HPP

#include "Weapon.hpp"  // Inclut la définition de la classe Weapon.
#include <string>
// Déclaration de la classe HumanB.
class HumanB {
private:
    std::string name;  // Variable membre privée pour stocker le nom de l'entité HumanB.
    Weapon *weapon;    // Pointeur sur un objet Weapon. Il est initialisé à nullptr dans le constructeur.

public:
    // Constructeur explicite prenant un std::string pour initialiser le nom de l'entité HumanB.
    // Ce constructeur n'initialise pas le pointeur 'weapon', donc 'weapon' doit être défini plus tard.
    HumanB(std::string name);

    // Méthode pour définir l'objet 'weapon' utilisé par HumanB. Cette méthode est nécessaire 
    // car le constructeur n'exige pas un objet 'weapon' lors de la création de l'objet HumanB.
    void setWeapon(Weapon &weapon);

    // Méthode pour simuler une attaque par HumanB. Cette méthode affiche un message indiquant 
    // que HumanB attaque, en utilisant le type de l'arme actuelle si une arme est définie.
    void attack() const;
};

#endif

