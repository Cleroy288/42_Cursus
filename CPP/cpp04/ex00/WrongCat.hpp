#ifndef WRONGCAT_HPP
#define WRONGCAT_HPP

# include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
	public :
		void makeSound(void) const;
		
		virtual ~WrongCat(void);

		WrongCat &operator=(const WrongCat &rhs);

		WrongCat(void);
		WrongCat(const WrongCat &copy);
};

#endif
