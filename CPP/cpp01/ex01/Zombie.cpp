// Zombie.cpp
#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie() {
    // Le constructeur par défaut peut être vide
}
/*
Zombie::Zombie(std::string name) : _name(name) {
    // Ce constructeur surchargé initialise directement un zombie avec un nom du zombie
}
*/
Zombie::~Zombie() {
    std::cout << _name << " is destroyed" << std::endl;
    // Message pour vérifier quand le Zombie est détruit
}

void Zombie::announce() const {
    std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(std::string name) {
    this->_name = name;
}
