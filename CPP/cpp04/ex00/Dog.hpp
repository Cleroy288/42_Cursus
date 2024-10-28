#ifndef DOG_HPP
#define DOG_HPP

# include "Animal.hpp"

class Dog : public Animal {
	public :
		virtual void makeSound(void) const;

		Dog &operator=(const Dog &rhs);

		Dog(void);
		Dog(const Dog &copy);
		
		virtual ~Dog(void);
};

#endif
