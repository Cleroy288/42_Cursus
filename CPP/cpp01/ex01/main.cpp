// main.cpp
#include "Zombie.hpp"


int main()
{
    int N = 10;  // ou tout autre nombre de zombies que vous voulez dans votre horde
    Zombie* horde = zombieHorde(N, "RegularZombie");

    for (int i = 0; i < N; ++i)
    {
        horde[i].announce();
    }

    delete[] horde;  // très important - cela libère la mémoire allouée pour la horde

    return 0;
}
