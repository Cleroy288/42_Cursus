# include "Animal.hpp"

Animal::Animal() : type("Animal") { std::cout << "Default constructor for Animal: A new Animal instance has been created with type 'Animal'" << std::endl; }

Animal::Animal(const Animal &copy) : type(copy.type) { std::cout << "Copy constructor for Animal: A copy of an Animal instance has been created with the same type" << std::endl; }

Animal::~Animal() { std::cout << "Destructor for Animal: The Animal instance has been destroyed" << std::endl; }

Animal &Animal::operator=(const Animal &rhs) {
	if (this != &rhs) {
		this->type = rhs.type;
		std::cout << "Assignment operator for Animal: The Animal instance has been assigned a new type" << std::endl;
	}
	return *this;
}

void Animal::makeSound() const { std::cout << "Generic Animal Sound: This Animal (" << this->type << ") makes a generic sound." << std::endl;}

std::string Animal::getType() const { return this->type; }
