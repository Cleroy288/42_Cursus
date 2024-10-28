#include "Zombie.hpp"

//en gros ici on fait appel à une sorte de malloc (new) on découvre ce que est un constructeur et un destructeur
//
int main()
{
    // Création d'un Zombie sur le tas
    Zombie* zombie1 = newZombie("Tas Zombie");
    zombie1->announce();

    //libérer la mémoire!
    delete zombie1;

    // Création d'un Zombie sur la pile
    randomChump("Pile Zombie");

    // Le zombie créé dans randomChump est automatiquement détruit

    return 0;
}
