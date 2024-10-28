#include "ClapTrap.hpp"

int main()
{
	ClapTrap	fighter( "<name>" );
	ClapTrap	bystander( "victim" );

	for (int i = 0; i < 12; ++i) {
		ClapTrap cortiz("Cortiz");
    ClapTrap fluchten("Fluchten");
    ClapTrap marwane("Marwane");

    std::cout << std::endl;
    std::cout << "\033[1;30m" << " Test 1 ~ ATTACK ~ " << "\033[0m" << std::endl;
    for (int i = 1; i <= 12; i++) {
        std::cout << i << ": ";
        cortiz.attack("Fluchten");
    }
    std::cout << std::endl;

    std::cout << "\033[1;31m" << " Test 2 ~ TAKE DAMAGE ~ " << "\033[0m" << std::endl;
    fluchten.takeDamage(7);
    fluchten.takeDamage(5);
    fluchten.takeDamage(1);
    fluchten.takeDamage(2);
    marwane.takeDamage(4);
    std::cout << std::endl;

    std::cout << "\033[1;32m" << "Test 3 ~ BE REPAIRED ~ " << "\033[0m" << std::endl;
    cortiz.beRepaired(3);
    fluchten.beRepaired(8);
    marwane.beRepaired(2);
    marwane.beRepaired(5);
    for (int i = 0; i < 10; i++){
        std::cout << i << ": ";
        marwane.beRepaired(i);
    }
    std::cout << std::endl;

    return (0);
	}
	return (0);
}