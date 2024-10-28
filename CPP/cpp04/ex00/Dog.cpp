#include "Dog.hpp"

Dog::Dog(void) {
	this->type = "Dog";
	std::cout << "Dog constructor called !" << std::endl;
}

Dog::Dog(const Dog &copy) {
	this->type = copy.type;
	std::cout << "Dog copy constructor called" << std::endl;
}

Dog::~Dog(void) { std::cout << "Dog destructor called !" << std::endl; }

Dog &Dog::operator=(const Dog &rhs) {
	this->type = rhs.type;
	std::cout << "Dog Assignation operator called !" << std::endl;
	return (*this);
}

void Dog::makeSound(void) const{
	std::cout << this->type << ": Woof woof !" << std::endl; }