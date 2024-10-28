#include "FragTrap.hpp"


std::string FragTrap::getName() const {
    return this->_name;
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name) {
	this->hitPoint = 100;
	this->energyPoint = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap \"" << this->_name << "\" constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap &copy) : ClapTrap(copy) {
	std::cout << "FragTrap copy constructor called" << std::endl;
}

FragTrap::~FragTrap(void) {
	std::cout << "FragTrap destructor called" << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &rhs) {
	std::cout << "FragTrap Assignation operator called" << std::endl;
	ClapTrap::operator=(rhs);
	return *this;
}

void FragTrap::highFivesGuys(void) {
	if (hitPoint > 0)
		std::cout << "High Five?" << std::endl;
	else 
		std::cout << "FragTrap \"" << this->_name << "\" is dead!" << std::endl;
}

FragTrap::FragTrap(void) : ClapTrap() {
	this->hitPoint = 100;
	this->energyPoint = 100;
	this->attackDamage = 30;
	std::cout << "FragTrap \"" << this->_name << "\" constructor called" << std::endl;
}