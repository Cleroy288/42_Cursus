#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"

int main()
{
    {//bloc de portée (locale) , ce qui est fait dans se bloc est libéré en dehors, cela est lié à la porte des variables et durée de vie des objets.
        Weapon club = Weapon("crude spiked club");

        HumanA bob("Bob", club);
        bob.attack();

        club.setType("some other type of club");
        bob.attack();
		// À la fin de ce bloc, les objets 'bob' et 'club' sont détruits.
    }

    {
        Weapon club = Weapon("crude spiked club");

        HumanB jim("Jim");
        jim.setWeapon(club);
        jim.attack();

        club.setType("some other type of club");
        jim.attack();
		// À la fin de ce bloc, les objets 'jim' et 'club' sont détruits.

    }
	//utiliser des blocs de portée est utile pour gérer la durée de vie des objets
	//permet en plus d'avoir 2 objets club pour chacun des pour HumanA et HumanB
    return 0;
}
