#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP

# include "ScavTrap.hpp"

class FragTrap : public ClapTrap {
	private :

	public :
		void highFivesGuys(void);
		std::string getName() const;

		FragTrap &operator=(const FragTrap &rhs);

		FragTrap(void);
		FragTrap(const std::string &name);
		FragTrap(const FragTrap &copy);
		~FragTrap(void);
};

#endif