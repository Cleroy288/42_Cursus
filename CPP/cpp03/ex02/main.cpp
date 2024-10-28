#include <iostream>
#include <string>
#include "FragTrap.hpp"

int main() {
    FragTrap traps[] = {FragTrap("pers1"), FragTrap("pers2"), FragTrap("pers3")};
    const int SIZE = sizeof(traps) / sizeof(FragTrap);

    std::cout << "\n\033[1;30mTest 1 ~ ATTACK ~\033[0m\n";
    traps[0].attack(traps[1].getName());
    traps[0].attack(traps[2].getName());
    
    std::cout << "\n\033[1;31mTest 2 ~ TAKE DAMAGE ~\033[0m\n";
    for (int i = 1; i < SIZE; ++i) {
        for (int damage = 1; damage <= 5; ++damage) {
            traps[i].takeDamage(damage * (i + 15));
        }
    }

    std::cout << "\n\033[1;32mTest 3 ~ BE REPAIRED ~\033[0m\n";
    for (int i = 0; i < SIZE; ++i) {
        traps[i].beRepaired(i + 3);
    }

    std::cout << "\n\033[1;34mTest 4 ~ HIGH FIVES GUYS ~\033[0m\n";
    for (int i = 0; i < SIZE; ++i) {
        traps[i].highFivesGuys();
    }

    return 0;
}

