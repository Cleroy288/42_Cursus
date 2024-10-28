#include "HumanA.hpp"
#include <iostream>

/**
 * Classe représentant un personnage humain de type A.
 * 
 * Constructeur: Initialise un objet HumanA avec un nom spécifique et une arme.
 * Ce constructeur lie directement l'objet HumanA à une instance d'arme spécifique 
 * (et non pas une copie de l'arme), permettant à l'objet HumanA d'accéder à cette 
 * arme et de la manipuler.
 * 
 * La méthode 'attack' permet au personnage humain de simuler une attaque, affichant 
 * un message à la console qui inclut le nom du personnage et le type d'arme utilisé.
 */

// Constructeur qui initialise le personnage avec un nom et une référence à une arme existante.
HumanA::HumanA(std::string name, Weapon &weapon) : name(name), weapon(weapon) {}//corps du constructeur est vide

// Méthode pour simuler une attaque avec l'arme du personnage.
void HumanA::attack() const {
    std::cout << name << " attacks with their " << weapon.getType() << std::endl;
}
