#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name)
{
    // allocation dynamique de N objets Zombie
    Zombie* horde = new Zombie[N];

    for (int i = 0; i < N; ++i)
	{
        // il y a plusieurs façons d'attribuer un nom, cela dépend de la structure de votre classe Zombie
        horde[i].setName(name);  // si vous avez une méthode pour définir le nom après la création
        // ou, si vous avez un constructeur qui prend un nom :
        // horde[i] = Zombie(name);
    }

    return horde;  // retourne un pointeur vers le premier zombie de la horde
}
