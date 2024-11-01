#ifndef ANIMAL_HPP
#define ANIMAL_HPP

# include <iostream>

class Animal {
	protected :
		std::string type;

	public :
		virtual void makeSound(void) const = 0;/// Fonction membre purement virtuelle chaque fonction en héritant (de animal) devras faire ça propre implémentation 
		std::string getType(void) const;

		Animal &operator=(const Animal &rhs);

		Animal(void);
		Animal(const Animal &copy);
        
		virtual ~Animal(void);
};

#endif

