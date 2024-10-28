/*
Exercice 00: "Bureaucrat"
    
Objectif:
    Créer une classe Bureaucrat avec un nom et un grade.

Fonctionnalités:
    Gérer les exceptions pour les grades trop hauts ou trop bas.
    Permettre d'augmenter ou de diminuer le grade du bureaucrate.

*/

#include "Bureaucrat.hpp"

int main() {
    try {
        Bureaucrat Alice("Alice", 50);
        Bureaucrat Nobodyy(100);
        Bureaucrat Jean_boss("Jean", 1);
        Bureaucrat Only_grade(150);
        Bureaucrat Copy(Jean_boss);

        print_string("---- print stats ----");
        Alice.Print_stats();
        Nobodyy.Print_stats();
        Jean_boss.Print_stats();
        Only_grade.Print_stats();
        Copy.Print_stats();

        print_string("--------------------");
        print_string("--- print promotion and demoted ---");

        try {
            Jean_boss.Promotion();
        } catch (std::exception& e) {
            std::cerr << "Exception caught while promoting: " << e.what() << std::endl;
        }

        try {
            Jean_boss.dePromotion();
            Only_grade.dePromotion();
            Only_grade.Promotion();
            Only_grade.dePromotion();
        } catch (std::exception& e) {
            std::cerr << "Unexpected exception: " << e.what() << std::endl;
        }

        print_string("--------------------");
		print_string("---- overload << -------");
        std::cout << Jean_boss << std::endl;
		print_string("-----------------------");

    } catch (std::exception& e) {
        std::cerr << "Unexpected exception: " << e.what() << std::endl;
    }

    print_string("--------------------");

	print_string("--------------------");


    // Traitement des cas exceptionnels de création de `Bureaucrat`
    try {
        Bureaucrat Jean_Baptiste("Jean", 255); // GradeTooLowException
    } catch (std::exception &e) {
        print_string("Error grade too low");
    }

    try {
        Bureaucrat Jean_Baptiste("Jean", 0); // GradeTooHighException
    } catch (std::exception &e) {
        print_string("Error grade too high");
    }

    return 0;
}
