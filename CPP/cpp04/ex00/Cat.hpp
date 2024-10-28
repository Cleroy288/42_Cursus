#ifndef CAT_HPP
#define CAT_HPP

# include "Animal.hpp"

class Cat : public Animal {
	public :
		virtual void makeSound(void) const;

		Cat &operator=(const Cat &rhs);

		Cat(void);
		Cat(const Cat &copy);
		
        virtual ~Cat(void);
};

#endif
