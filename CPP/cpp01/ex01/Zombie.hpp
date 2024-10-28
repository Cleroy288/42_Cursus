// Zombie.hpp
#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
public:
    Zombie();  // le constructeur peut être standard si vous initialisez via une méthode séparée
    ~Zombie();  // n'oubliez pas le destructeur

    void announce() const;
    void setName(std::string name);  // si vous utilisez une méthode d'initialisation séparée

private:
    std::string _name;
};

Zombie* zombieHorde(int N, std::string name);

#endif
