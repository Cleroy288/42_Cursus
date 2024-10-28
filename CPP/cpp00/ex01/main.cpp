#include "PhoneBook.hpp"

int main()
{
    PhoneBook       phoneBook;
    std::string     command;

    while (true)
    {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        std::getline(std::cin, command); // Cette ligne lit toute la ligne de commande

        //??fix bug avec search
        if (command.empty())
        {
            continue; // Ignore l'itération actuelle + demande une nouvelle entrée
        }
        
        // Extraire le premier mot de la commande (jusqu'au premier espace)
        std::string firstWord = command;
        if (firstWord == "ADD")
        {
            phoneBook.addContact();
        }
        else if (firstWord == "SEARCH")
        {
            phoneBook.searchAndDisplay();
        }
        else if (firstWord == "EXIT") 
        {
            std::cout << "Goodbye!" << std::endl;
            break;  // Sortir de la boucle while, terminant le programme finito pipo
        }
        else
        {
            std::cout<<"|"<<command<<"|"<<"\n";
            std::cout << "Invalid command!" << std::endl;
        }

    }
    return 0;
}

