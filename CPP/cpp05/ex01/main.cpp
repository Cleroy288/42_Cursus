/*

Exercice 01: "Form"
    Objectif:
        Ajouter une classe Form pour gérer des formulaires.
    Fonctionnalités:
        Chaque formulaire a un nom, un indicateur de signature, et des grades requis pour le signer et l'exécuter.
        Gérer les exceptions pour les grades requis hors limites.
        Les bureaucrates peuvent signer des formulaires.

*/

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main() {
    try {
        print_string("----- TESTS -----");
        print_string("----- BUREAUCRAT -----");
        Bureaucrat alice("Alice", 5);
        Bureaucrat bob("Bob", 150);
        Bureaucrat Charlie(bob);
        Form form1("Form1", 10, 5);
        Form form2("Form2", 1, 1);
        Form form3(form2);
        print_string("-----  -----");
        print_string("----- <<  test -----");
        std::cout << alice << std::endl;
        std::cout << bob << std::endl;
        std::cout << form1 << std::endl;
        std::cout << form2 << std::endl;
        print_string("-----  -----");
        print_string("----- signForm test -----");

        alice.signForm(form1);

        bob.signForm(form2);
        print_string("-----  -----");
        print_string("----- forms states -----");

        std::cout << form1 << std::endl;
        std::cout << form2 << std::endl;
        print_string("-----  -----");
        print_string("----- assignation operator test -----");

        Form formCopy = form1;
        std::cout << "Form copy: " << formCopy << std::endl;
        print_string("-----  -----");
        print_string("----- be signed && signForm test -----");
        form1.beSigned(alice);
        alice.signForm(form1);
        print_string("-----  -----");
        print_string("--- be signed bad ret msg test ----");
        bob.signForm(form2);
        print_string("-----  -----");

    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    print_string("----- TESTS exceptions -----");
    print_string("----- too high -------");
    try {
        Form formInvalid("InvalidForm", -200, -200);
    } catch (const Form::GradeTooHighException &e) {
        std::cerr << "Form::GradeTooHighException: " << e.what() << std::endl;
    } catch (const Form::GradeTooLowException &e) {
        std::cerr << "Form::GradeTooLowException: " << e.what() << std::endl;
    }
    print_string("----- too low -------");
    try {
        Form formInvalid("InvalidForm", 200, 200);
    } catch (const Form::GradeTooHighException &e) {
        std::cerr << "Form::GradeTooHighException: " << e.what() << std::endl;
    } catch (const Form::GradeTooLowException &e) {
        std::cerr << "Form::GradeTooLowException: " << e.what() << std::endl;
    }

    return 0;
}

