#include "Zombie.hpp"

void randomChump(std::string name)
{
    Zombie zombie(name); // création sur la pile
    zombie.announce();
    // Pas besoin de delete, le destructeur sera appelé automatiquement après
}
