#include "Weapon.hpp"  // Inclut la définition de la classe Weapon.

// Constructeur avec des paramètres : il initialise l'attribut 'type' avec la valeur passée.
Weapon::Weapon(std::string type) : type(type) {
    // L'initialisation est faite en utilisant la liste d'initialisation du constructeur ci-dessus.
    // Pas d'autres opérations requises dans le corps du constructeur.
}

// Méthode 'getType' qui renvoie une référence constante à l'attribut privé 'type'.
// En renvoyant une référence constante, on s'assure que la valeur originale ne peut pas être modifiée.
const std::string &Weapon::getType() const {
    return type;  // Retourne directement la référence à 'type'.
}

// Méthode 'setType' utilisée pour modifier la valeur de l'attribut 'type'.
// Accepte une nouvelle valeur pour 'type' et l'assigne.
void Weapon::setType(std::string newType) {
    type = newType;  // Modifie la valeur de 'type'.
    // Après l'assignation, la méthode se termine, et 'type' contient désormais la nouvelle valeur.
}
