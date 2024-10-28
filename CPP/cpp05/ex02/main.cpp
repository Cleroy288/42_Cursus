/*

Exercice 02: "Concrete Forms"

Objectif:
    Créer des classes concrètes de formulaires (ShrubberyCreationForm, RobotomyRequestForm, PresidentialPardonForm) héritant de Form.
Fonctionnalités:
    ShrubberyCreationForm: Créer un fichier et y dessiner un arbre ASCII.
    RobotomyRequestForm: Simuler une robotomisation avec une chance de succès de 50%.
    PresidentialPardonForm: Annoncer un pardon présidentiel.
    Les bureaucrates peuvent exécuter ces formulaires.

Particularité: Cet exercice est le plus complexe car il introduit des actions spécifiques pour chaque type de
formulaire et nécessite une bonne compréhension de l'héritage, du polymorphisme, et de la gestion des exceptions.

*/

#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <cstdlib> // Pour rand() et srand()
#include <ctime>   // Pour time()

void    test_pardonform() {
    try {
        print_string("----- TEST PRESIDENTIALPARDONFORM -----\n");

        print_string("----- Test 1: Création ----");
        // Création d'un bureaucrate et d'un formulaire de grâce présidentielle
        Bureaucrat bureaucrat("Alice", 5); // Un grade suffisamment élevé pour signer et exécuter
        PresidentialPardonForm pardonForm("Bob");
        Bureaucrat Useless("Useless", 150);



        print_string("\n----- affichage ");
        std::cout << bureaucrat << std::endl;
        std::cout << pardonForm << std::endl;
        print_string("----- ");
        print_string("----- Test 2: Signature du formulaire par un bureaucrate\n");
        // Tentative de signature du formulaire par le bureaucrate
        try {
            bureaucrat.signForm(pardonForm);
        } catch (const std::exception& e) {
            std::cerr << "Error when trying to sign: " << e.what() << std::endl;
        }

        print_string("----- ");
        print_string("----- Test 3: Tentative de signature par un bureaucrate avec un grade suffisant\n");
        std::cout << pardonForm << std::endl;
        // Tentative d'exécution du formulaire par le bureaucrate
        try {
            bureaucrat.executeForm(pardonForm);
        } catch (const std::exception& e) {
            std::cerr << "Erreur when trying to execute: " << e.what() << std::endl;
        }

        print_string("\n----- Usless missing everything ------");
        try {
            Useless.executeForm(pardonForm);
        } catch (const std::exception& e) {
            std::cerr << "Erreur when trying to execute: " << e.what() << std::endl;
        }

        try {
            Useless.signForm(pardonForm);
        } catch (const std::exception& e) {
            std::cerr << "Erreur when trying to sign: " << e.what() << std::endl;
        }

        print_string("\n------");

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }



    print_string("----- TEST PRESIDENTIALPARDONFORM END-----\n\n");
}

void    test_robotomy()
{
    try {
    print_string("----- TEST ROBOTOMYREQUESTFORM -----");
    // Initialisation du générateur de nombres aléatoires
    srand(static_cast<unsigned int>(time(nullptr)));//nécessaire pour rand()

    // Test 1: Création et affichage d'un formulaire RobotomyRequestForm
    std::cout << "----- Test 1: Création et affichage d'un RobotomyRequestForm" << std::endl;
    RobotomyRequestForm robotomyForm("Target1");

    // Test 2: Signature du formulaire par un bureaucrate avec un grade suffisant
    std::cout << "\n----- Test 2: Signature du formulaire par un bureaucrate avec un grade suffisant" << std::endl;
    Bureaucrat bureaucratHigh("Alice", 5); // Grade suffisamment élevé pour signer
    bureaucratHigh.signForm(robotomyForm);

    // Test 3: Tentative de signature par un bureaucrate avec un grade insuffisant
    std::cout << "\n---- Test 3: Tentative de signature par un bureaucrate avec un grade insuffisant" << std::endl;
    Bureaucrat bureaucratLow("Bob", 150); // Grade insuffisant pour signer
    bureaucratLow.signForm(robotomyForm);

    // Test 4: Exécution du formulaire par un bureaucrate avec un grade suffisant
    std::cout << "\n----- Test 4: Exécution du formulaire par un bureaucrate avec un grade suffisant" << std::endl;
    bureaucratHigh.executeForm(robotomyForm);

    // Test 5: Tentative d'exécution par un bureaucrate avec un grade insuffisant
    std::cout << "\n----- Test 5: Tentative d'exécution par un bureaucrate avec un grade insuffisant" << std::endl;
    bureaucratLow.executeForm(robotomyForm);

    print_string("----- ");
    } catch (const std::exception & e) {
        std::cerr << "Error : " << e.what() << std::endl;
    }
    print_string("\n----- TEST ROBOTOMYREQUESTFORM END-----\n\n");
}

void    test_shrubby() {
        try {
        // Créer des bureaucrates
        print_string("----- TEST SHRUBBERYCREATIONFORM -----\n");
        print_string("----- Test 1: Création Bureaucrate and Shrubby -----\n");
        print_string("- Bureacrate Alice (grade high) and Bob (grade low) -");
        Bureaucrat alice("Alice", 5); // Un grade élevé
        Bureaucrat bob("Bob", 150);   // Un grade bas

        // Créer des formulaires
        print_string("- ShrubberyCreationForm, RobotomyRequestForm, PresidentialPardonForm -");
        ShrubberyCreationForm shrubberyForm("home");
        RobotomyRequestForm robotomyForm("Marvin");
        PresidentialPardonForm pardonForm("Ford");
        print_string("-----");

        // Testez la signature et l'exécution avec Alice (devrait réussir)
        print_string("----tes with alice high grade ----");
        alice.signForm(shrubberyForm);
        alice.executeForm(shrubberyForm);

        alice.signForm(robotomyForm);
        alice.executeForm(robotomyForm);

        alice.signForm(pardonForm);
        alice.executeForm(pardonForm);
        print_string("-----");
        print_string("----- Test 2: Test with bob low grade (should fail ... at some point like ... quick)-----\n");
        // Testez la signature et l'exécution avec Bob (devrait échouer)
        bob.signForm(shrubberyForm);
        bob.executeForm(shrubberyForm);

        bob.signForm(robotomyForm);
        bob.executeForm(robotomyForm);

        bob.signForm(pardonForm);
        bob.executeForm(pardonForm);
        print_string("----- ");
        print_string("\n----- end of test shrubby  ----\n\n");

    } catch (const std::exception& e) {
        std::cerr << "Exception capturée: " << e.what() << std::endl;
    }

}

int main() {
    test_pardonform();
    test_robotomy();
    test_shrubby();

    print_string("----- that the best i can do ----\n");
    return 0;
}





