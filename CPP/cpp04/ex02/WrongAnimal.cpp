# include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("WrongAnimal") { std::cout << "Default constructor for WrongAnimal: An instance of WrongAnimal has been created" << std::endl; }

WrongAnimal::WrongAnimal(const WrongAnimal &copy) : type(copy.type) { std::cout << "Copy constructor for WrongAnimal: A copy of WrongAnimal has been created" << std::endl; }

WrongAnimal::~WrongAnimal() { std::cout << "Destructor for WrongAnimal: The WrongAnimal instance has been destroyed" << std::endl; }

void WrongAnimal::makeSound() const { std::cout << "WrongAnimal " << this->type << " makes a sound: ... (Undefined sound for WrongAnimal)" << std::endl; }

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &rhs) {
	if (this != &rhs) {
		this->type = rhs.type;
		std::cout << "Assignment operator for WrongAnimal: WrongAnimal has been assigned a new type" << std::endl;
	}
	return *this;
}

std::string WrongAnimal::getType() const { return this->type; }
