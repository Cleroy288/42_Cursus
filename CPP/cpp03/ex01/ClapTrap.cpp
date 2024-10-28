#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void) : _name("Default"), hitPoint(10), energyPoint(10), attackDamage(0) {
	std::cout << "ClaptTrap \"" << this->_name << "\" constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), hitPoint(10), energyPoint(10), attackDamage(0) {
	std::cout << "ClaptTrap \"" << this->_name << "\" constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &value) {
	std::cout << "ClaptTrap " << "Copy constructor called" << std::endl;
	*this = value;
}

ClapTrap::~ClapTrap(void){
	std::cout << "ClaptTrap " << "Destructor called" << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &rhs) {
	std::cout << "ClapTrap Assignation operator called" << std::endl;
	this->_name = rhs._name;
	this->hitPoint = rhs.hitPoint;
	this->energyPoint = rhs.energyPoint;
	this->attackDamage = rhs.attackDamage;
	return *this;
}


void ClapTrap::attack(const std::string &target) {
	if (hitPoint > 0 && energyPoint > 0)
	{
		std::cout << "ClapTrap \"" << this->_name << "\" attack " << target << ", causing " << this->attackDamage << " point of damage!" << std::endl;
		energyPoint--;
	}
	else if (hitPoint == 0)
		std::cout << "\"" << this->_name << "\" is dead he cannot perform any action !!" << std::endl;
	else
		std::cout << "Not enough energy :(" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
	if (hitPoint > 0)
	{
		std::cout << "\"" << this->_name << "\" suffered " << amount << " point of damage" << std::endl;
		if ((hitPoint - amount) > 0)
			hitPoint -= amount;
		else
			hitPoint = 0;
	}
	else
		std::cout << "\"" << this->_name << "\" is already dead stop bulying him !!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (hitPoint > 0 && energyPoint > 0)
	{
		std::cout << "\"" << this->_name << "\" repared about " << amount << " hp" << std::endl;
		energyPoint--;
		hitPoint += amount;
	}
	else if (hitPoint == 0)
		std::cout << "\"" << this->_name << "\" is dead he cannot perform any action !!" << std::endl;
	else
		std::cout << "Not enough energy :(" << std::endl;
}