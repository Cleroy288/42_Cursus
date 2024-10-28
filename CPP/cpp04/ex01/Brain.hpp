#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>

class Brain {
	private :
		std::string ideas[100];

	public :
		Brain &operator=(const Brain &rhs);

		Brain(void);
		Brain(const Brain &copy);
		
		~Brain(void);
};

#endif