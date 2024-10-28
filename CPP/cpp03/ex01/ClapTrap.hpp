#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

# include <iostream>

class ClapTrap {
	protected :
		std::string _name;
		int hitPoint;
		int energyPoint;
		int attackDamage;

	public :
		void attack(const std::string &target);
		void takeDamage(unsigned int amount);
		void beRepaired(unsigned int amount);

		ClapTrap &operator=(const ClapTrap &rhs);

		ClapTrap(void);
		ClapTrap(const ClapTrap &value);
		ClapTrap(std::string name);
		~ClapTrap(void);
};

#endif
