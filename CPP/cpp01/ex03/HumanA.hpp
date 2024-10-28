#ifndef HUMANA_HPP
#define HUMANA_HPP

#include "Weapon.hpp"  // Inclut la définition de la classe Weapon
#include <string> 

// Définition de la classe HumanA. Un HumanA == un combattant avec une arme.
class HumanA {
private:
    std::string name;  // Nom privé du combattant, ne peut pas être accédé directement en dehors de cette classe.
    Weapon &weapon;  // Référence à un objet Weapon. Cela signifie que chaque HumanA doit avoir une arme 
                     // et cette arme existe en dehors de la classe HumanA (elle n'est pas créée ni détruite par HumanA).

public:
    // Constructeur de HumanA. Il nécessite un nom (sous forme de chaîne) et une référence à un objet Weapon existant.
    // La référence garantit que ==> nous utilisons une arme qui existe déjà et non une copie de l'arme.
    HumanA(std::string name, Weapon &weapon);

    // Fonction membre publique pour simuler une attaque. Ceci est const, indiquant que la fonction ne modifie pas l'état de l'objet.
    void attack() const;
};

#endif

