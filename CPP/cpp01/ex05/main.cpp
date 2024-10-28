#include "Harl.hpp"

int main () 
{
	Harl	comp = Harl();
	comp.complain("DEBUG");
	comp.complain("INFO");
	comp.complain("WARNING");
	comp.complain("ERROR");
	comp.complain("nothing");
}