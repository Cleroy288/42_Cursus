#include "Cat.hpp"

Cat::Cat() {
	this->type = "cat";
	std::cout << "Default constructor for Cat: A new Cat instance has been created with type 'Cat'" << std::endl;
}

Cat::Cat(const Cat &copy) {
	this->type = copy.type;
	std::cout << "Copy constructor for Cat: A copy of a Cat instance has been created with the same type" << std::endl;
}

Cat::~Cat() { std::cout << "Destructor for Cat: The Cat instance has been destroyed" << std::endl; }

Cat &Cat::operator=(const Cat &rhs) {
	if (this != &rhs) {
		this->type = rhs.type;
		std::cout << "Assignment operator for Cat: The Cat instance has been assigned a new type" << std::endl;
	}
	return *this;
}

void Cat::makeSound() const { std::cout << this->type << ": MEOW !!!" << std::endl; }
