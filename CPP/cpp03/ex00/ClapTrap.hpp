#include <iostream>
#include <string>

class ClapTrap
{
	private:
		std::string _name;
		int 		hitPoints;
		int 		energyPoints;
		int 		attackDammage;

	public:
		//constructeurs et destructeur
		ClapTrap(void);
		ClapTrap(std::string name);
		ClapTrap(const ClapTrap &other);
		~ClapTrap(void);

		//Ajoutez au ClapTrap ces fonctions membres publiques afin de lui donner vie :
		void attack(const std::string& target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);

		//surcharge opérateur d'affectation
		ClapTrap &operator=(const ClapTrap &rhs);

		
};