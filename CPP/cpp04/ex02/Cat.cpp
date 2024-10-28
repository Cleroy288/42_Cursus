#include "Cat.hpp"

Cat::Cat() {
	this->type = "cat";
	this->brain = new Brain();

	std::cout << "Default constructor for Cat: A new Cat instance has been created with type 'Cat'" << std::endl;
}

Cat::Cat(const Cat &copy) {
	this->type = copy.type;
	std::cout << "Copy constructor for Cat: A copy of a Cat instance has been created with the same type" << std::endl;
}

Cat::~Cat() {
	delete this->brain;

	std::cout << "Destructor for Cat: The Cat instance has been destroyed" << std::endl;
}

Cat &Cat::operator=(const Cat &rhs) {//Apparement c'est comme cela qu'on fait une copie profonde :/
    if (this != &rhs) { // Protection contre l'auto-affectation
        this->type = rhs.type;

        // Supp l'ancien Brain s'il existe
        delete this->brain;

        // Créer un nvx Brain et copier le contenu
        if (rhs.brain != nullptr) {
            this->brain = new Brain(*rhs.brain);
        } else {
            this->brain = nullptr;
        }
    }
    std::cout << "Cat Assignation operator called" << std::endl;
    return *this;
}


void Cat::makeSound() const { std::cout << this->type << ": MEOW !!!" << std::endl; }
