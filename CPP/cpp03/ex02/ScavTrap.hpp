#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

# include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
	private :

	public :
		void attack(const std::string &target);
		void guardGate(void);

		ScavTrap &operator=(const ScavTrap &rhs);
		std::string getName() const;


		ScavTrap(void);
		ScavTrap(const ScavTrap &copy);
		ScavTrap(std::string name);
		~ScavTrap(void);
};

#endif