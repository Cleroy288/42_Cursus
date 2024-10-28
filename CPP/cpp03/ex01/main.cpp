#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
    const int SIZE = 3;
    ScavTrap scavTraps[SIZE] = {
        ScavTrap("pers1"),
        ScavTrap("pers2"),
        ScavTrap("pers3")
    };

    std::cout << "\n\033[1;30mTest 1 ~ ATTACK ~\033[0m\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (i != j) {
                scavTraps[i].attack(scavTraps[j].getName());
            }
        }
    }

    std::cout << "\n\033[1;31mTest 2 ~ TAKE DAMAGE ~\033[0m\n";
    for (int i = 0; i < SIZE; ++i) {
        scavTraps[i].takeDamage(25);
    }

    std::cout << "\n\033[1;32mTest 3 ~ BE REPAIRED ~\033[0m\n";
    for (int i = 0; i < SIZE; ++i) {
        scavTraps[i].beRepaired(10);
    }

    std::cout << "\n\033[1;36mTest 4 ~ GUARD GATE ~\033[0m\n";
    for (int i = 0; i < SIZE; ++i) {
        scavTraps[i].guardGate();
    }

    return 0;
}
