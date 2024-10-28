#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name("Def"), hitPoints(10), energyPoints(10), attackDammage(10) {
	std::cout<<"Default constructor called"<<std::endl;
	return ;
};

ClapTrap::ClapTrap(std::string name) : _name(name), hitPoints(10), energyPoints(10), attackDammage(10) {
	std::cout<<"Name setter constructor from "<<this->_name<<" was called"<<std::endl;
	return ;
};

ClapTrap::ClapTrap(const ClapTrap &other) {
	*this = other;
	std::cout<<"Copy constructor called"<<std::endl;
	return ;
};

ClapTrap::~ClapTrap() {
	std::cout<<"Destructor called of "<<this->_name<<std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other) {
	std::cout << "Copy assignment operator called" << std::endl;
	this->_name = other._name;
	this->hitPoints = other.hitPoints;
	this->energyPoints = other.energyPoints;
	this->attackDammage = other.attackDammage;
	return (*this);
}

void ClapTrap::attack(const std::string &target) {
	if (hitPoints > 0 && energyPoints > 0)
	{
		std::cout << "ClapTrap " << this->_name << " attack " << target << ", causing " << this->attackDammage << " point of damage!" << std::endl;
		energyPoints--;
	}
	else if (hitPoints == 0)
		std::cout << this->_name << " is dead he cannot perform any action !!" << std::endl;
	else
		std::cout << "Not enough energy :(" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
	if (hitPoints > 0)
	{
		std::cout << "ClapTrap " << this->_name << " suffered " << amount << " point of damage" << std::endl;
		if ((hitPoints - amount) > 0)
			hitPoints -= amount;
		else
			hitPoints = 0;
	}
	else
		std::cout << "ClapTrap " << this->_name << " is already dead stop bulying him !!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (hitPoints > 0 && energyPoints > 0)
	{
		std::cout << "ClapTrap " << this->_name << " repared about " << amount << " hp" << std::endl;
		energyPoints--;
		hitPoints += amount;
	}
	else if (hitPoints == 0)
		std::cout << this->_name << " is dead he cannot perform any action !!" << std::endl;
	else
		std::cout << "Not enough energy :(" << std::endl;
}