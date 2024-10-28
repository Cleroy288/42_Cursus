#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>  // Inclut la bibliothèque de chaînes standard pour utiliser l'objet std::string.

// Définition de la classe Weapon.
class Weapon {
private:
    // Déclaration d'un membre privé de type std::string. 
    // Il est privé pour restreindre l'accès direct et assurer le contrôle via les méthodes publiques.
    std::string type;

public:
    // Déclaration du constructeur qui prend une chaîne de caractères en paramètre.
    // Ce constructeur est utilisé pour initialiser l'objet Weapon avec un type spécifique.
    Weapon(std::string type);

    // Déclaration d'une méthode constante 'getType' qui retourne une référence à la chaîne de caractères constante.
    // Cette méthode permet d'accéder à la valeur du membre 'type' depuis l'extérieur de la classe.
    const std::string &getType() const;

    // Déclaration de la méthode 'setType' qui prend une nouvelle valeur pour 'type'.
    // Cette méthode permet de modifier la valeur de l'attribut 'type' après la création de l'objet.
    void setType(std::string type);
};

#endif

