#include "Brain.hpp"

Brain::Brain(void) { std::cout << "Brain constructor called !" << std::endl; }

Brain::Brain(const Brain &copy) {
	std::cout << "Brain copy constructor called !" << std::endl;
	*this = copy;
}

Brain::~Brain(void) { std::cout << "Brain destructor called !" << std::endl; }

Brain &Brain::operator=(const Brain &rhs) {
	for (int i = 0; i < 100; i++)
		this->ideas[i] = rhs.ideas[i];
	std::cout << "Brain Assignation operator called !" << std::endl;
	return (*this);
}