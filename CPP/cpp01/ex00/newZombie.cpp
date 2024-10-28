#include "Zombie.hpp"

Zombie* newZombie(std::string name)
{
    Zombie* zombie = new Zombie(name); // création sur le tas
    return zombie;
}
