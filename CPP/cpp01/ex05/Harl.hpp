#ifndef HARL_HPP
#define HARL_HPP

#include <iostream>

class Harl {
	private :
		void	info(void);
		void	debug(void);
		void	warning(void);
		void	error(void);
		void	(Harl::*options[4])(void);

	public :
		void	complain(std::string level);
		Harl(void);
		~Harl(void);
};

#endif