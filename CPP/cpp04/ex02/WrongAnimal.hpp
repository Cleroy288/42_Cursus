#ifndef WRONGANIMAL_HPP
#define WRONGANIMAL_HPP

# include <iostream>

class WrongAnimal {
	protected :
		std::string type;

	public :
		void makeSound(void) const;
		std::string getType(void) const;

		WrongAnimal &operator=(const WrongAnimal &rhs);

		WrongAnimal(void);
		WrongAnimal(const WrongAnimal &copy);
		
		virtual ~WrongAnimal(void);
};

#endif
