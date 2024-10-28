/*

Exercice 03: "Intern"

Objectif:
    Créer une classe Intern capable de générer des formulaires.

Fonctionnalités:
    La fonction makeForm crée un formulaire en fonction de son nom et de sa cible.
    Gestion des noms de formulaires invalides avec des messages d'erreur appropriés.
    L'intern ne possède pas d'attributs uniques, il est utilisé uniquement pour créer des formulaires.

*/

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour time()
#include "Intern.hpp"

int main() {
    Intern someRandomIntern;
    Bureaucrat highRankedBureaucrat("Alice", 1); // Un bureaucrate avec un grade élevé pour signer et exécuter des formulaires.

    // Tableaux des noms de cibles et des formulaires
    const std::string targets[] = {"Home", "Robot", "President"};
    const std::string forms[] = {"shrubbery creation", "robotomy request", "presidential pardon", "invalid form"};

    // Utilisez une boucle classique pour parcourir les tableaux
    for (int i = 0; i < 4; ++i) {
        const std::string& formName = forms[i];
        AForm* form = someRandomIntern.makeForm(formName, targets[0]);
        if (form) {
            std::cout << *form << std::endl;
            highRankedBureaucrat.signForm(*form);
            highRankedBureaucrat.executeForm(*form);
            delete form; // Nettoyer la mémoire allouée
        }
        print_string("--------------------------------------------------");
    }

    return 0;
}





