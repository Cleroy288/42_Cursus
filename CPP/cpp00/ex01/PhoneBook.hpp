#include <iostream>
#include <iomanip> // Pour std::setw et std::setfill
#include <string>
#include <limits>  // Pour std::numeric_limits

class Contact {
private:
    std::string firstName, lastName, nickname, phoneNumber, darkestSecret;

public:
    void setContact()
    {
        std::string input;  // variable pour stocker chaque ligne d'entrée

        std::cout << "Enter first name: ";
        std::getline(std::cin, input);
        firstName = input;  // extrait le premier mot

        std::cout << "Enter last name: ";
        std::getline(std::cin, input);
        lastName = input;  // extrait le premier mot

        std::cout << "Enter nickname: ";
        std::getline(std::cin, input);
        nickname = input;  // extrait le premier mot

        std::cout << "Enter phone number: ";
        std::getline(std::cin, input);
        phoneNumber = input;  // extrait le premier mot

        std::cout << "Enter darkest secret: ";
        std::getline(std::cin, input);
        darkestSecret = input;  // extrait le premier mot
    }

    void displaySummary(int index) const
    {
        // Affiche l'index et les trois premières colonnes (tronquées si nécessaire)
        std::cout << "|" << std::setw(10) << index;
        std::cout << "|" << std::setw(10) << truncate(firstName);
        std::cout << "|" << std::setw(10) << truncate(lastName);
        std::cout << "|" << std::setw(10) << truncate(nickname) << "|" << std::endl;
    }

    void displayFullInfo() const
    {
        std::cout << "First name: " << firstName << "\nLast name: " << lastName
                  << "\nNickname: " << nickname << "\nPhone number: " << phoneNumber
                  << "\nDarkest secret: " << darkestSecret << std::endl;
    }

    // Utilitaire pour tronquer les chaînes de caractères si elles sont trop longues
    static std::string truncate(const std::string &str)
    {
        return (str.length() > 10) ? str.substr(0, 9) + '.' : str;
    }
};

class PhoneBook
{
private:
    Contact contacts[8];
    int nextIndex;  // L'index du prochain contact à ajouter
    int numContacts;  // Le nombre total de contacts actuellement enregistrés

public:
    PhoneBook() : nextIndex(0), numContacts(0) {}  // initialisation de nextIndex et numContacts à 0

    void addContact() {
        if (numContacts < 8)
        {  // si < 8
            contacts[nextIndex].setContact();  // set info contact à index
            numContacts++;  // Augmenter le nombre de contacts
        }
        else
        {//sinon on passe à 0
            contacts[nextIndex].setContact();  // Écraser l'ancien contact
        }
        nextIndex = (nextIndex + 1) % 8;

    }

    void searchAndDisplay() const
    {
        if (numContacts == 0)
        {
            std::cout << "Phonebook is empty.\n";
            return;
        }

        std::cout << "|" << std::setw(10) << "index" << "|" << std::setw(10) << "first name"
                  << "|" << std::setw(10) << "last name" << "|" << std::setw(10) << "nickname" << "|" << std::endl;

        for (int i = 0; i < numContacts; ++i)
        {  // Utilisation de numContacts pour l'itération
            contacts[i].displaySummary(i + 1);
        }

        std::cout << "Enter the index of the contact you want to view: ";
        int index;
        std::cin >> index;

        if (std::cin.fail() || index <= 0 || index > numContacts)
        {  // Vérification basée sur numContacts
            std::cout << "Invalid index.\n";
            std::cin.clear();  // efface les erreurs d'entrée
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // ignore la ligne incorrecte
        }
        else
        {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            contacts[index - 1].displayFullInfo();
        }
    }
};
