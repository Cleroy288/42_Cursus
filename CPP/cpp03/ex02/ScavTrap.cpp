#include "ScavTrap.hpp"

std::string ScavTrap::getName() const {
    return this->_name;
}


ScavTrap::ScavTrap(void) : ClapTrap() {
	hitPoint = 100;
	energyPoint = 50;
	attackDamage = 20;
	std::cout << "ScavTrap \"" << this->_name << "\" constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &copy) : ClapTrap(copy) {
	std::cout << "ScavTrap copy constructor called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
	hitPoint = 100;
	energyPoint = 50;
	attackDamage = 20;
	std::cout << "ScavTrap \"" << this->_name << "\" constructor called" << std::endl;
}

ScavTrap::~ScavTrap(void) {
	std::cout << "ScavTrap \"" << this->_name << "\" destructor called" << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &rhs) {
	std::cout << "ScavTrap Assignation operator called" << std::endl;
	ClapTrap::operator=(rhs);
	return *this;
}

void ScavTrap::attack(const std::string &target) {
	if (hitPoint > 0 && energyPoint > 0)
	{
		std::cout << "ScavTrap \"" << this->_name << "\" attack " << target << ", causing " << this->attackDamage << " point of damage!" << std::endl;
		energyPoint--;
	}
	else if (hitPoint == 0)
		std::cout << "ScavTrap \"" << this->_name << "\" is dead he cannot perform any action !!" << std::endl;
	else
		std::cout << "ScavTrap \"" << this->_name << "\": not enough energy :(" << std::endl;
}

void ScavTrap::guardGate(void)  {
	if (this->hitPoint <= 0)
		std::cout << "ScavTrap \"" << this->_name << "\" cannot enter Gate Keeper mode!" << std::endl;
	else
		std::cout << "ScavTrap \"" << this->_name << "\" entered Gate Keeper mode" << std::endl;
}