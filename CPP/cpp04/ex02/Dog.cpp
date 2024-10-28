#include "Dog.hpp"

Dog::Dog(void) {
	this->type = "Dog";
	this->brain = new Brain();

	std::cout << "Dog constructor called !" << std::endl;
}

Dog::Dog(const Dog &copy) {
	this->type = copy.type;
	std::cout << "Dog copy constructor called" << std::endl;
}

Dog::~Dog(void) {
	delete this->brain;

	std::cout << "Dog destructor called !" << std::endl;
}

Dog &Dog::operator=(const Dog &rhs) {
    if (this != &rhs) { // Protection contre l'auto-affectation
        this->type = rhs.type;

        // Supprimer l'ancien Brain s'il existe
        delete this->brain;

        // Créer un nouveau Brain et copier le contenu
        if (rhs.brain != nullptr) {
            this->brain = new Brain(*rhs.brain);
        } else {
            this->brain = nullptr;
        }
    }
    std::cout << "Dog Assignation operator called !" << std::endl;
    return *this;
}


void Dog::makeSound(void) const{ std::cout << this->type << ": Woof woof !" << std::endl; }