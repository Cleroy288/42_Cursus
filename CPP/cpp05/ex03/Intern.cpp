#include "Intern.hpp"
#include <iostream>

/*
** ------------------------------- CONSTRUCTOR  && DESTRUCTOR --------------------------------
*/


Intern::Intern() {
	print_string("constructor of Intern called");
}

Intern::Intern(const Intern& other) {
    (void)other;
	print_string("copy constructor of Intern called");
}

Intern& Intern::operator=(const Intern& other) {
    print_string("assignation operator of Intern called");
	(void)other;
    return *this;
}

Intern::~Intern() {
	print_string("destructor of Intern called");
}


/*
** --------------------------------- METHODS ----------------------------------
*/


AForm* Intern::makeForm(const std::string& formName, const std::string& target) const {
    struct FormPair {
        std::string name;
        AForm* (Intern::*function)(const std::string& target) const;
    };

    FormPair forms[] = {
        {"shrubbery creation", &Intern::makeShrubberyCreationForm},
        {"robotomy request", &Intern::makeRobotomyRequestForm},
        {"presidential pardon", &Intern::makePresidentialPardonForm}
    };

    for (int i = 0; i < 3; ++i) {
        if (forms[i].name == formName) {
            std::cout << "Intern creates " << formName << std::endl;
            return (this->*(forms[i].function))(target);
        }
    }

    std::cerr << "Intern: Form name '" << formName << "' is invalid." << std::endl;
    return nullptr;
}

AForm* Intern::makeShrubberyCreationForm(const std::string& target) const {
	print_string("makeShrubberyCreationForm called");
    return new ShrubberyCreationForm(target);
}

AForm* Intern::makeRobotomyRequestForm(const std::string& target) const {
	print_string("makeRobotomyRequestForm called");
    return new RobotomyRequestForm(target);
}

AForm* Intern::makePresidentialPardonForm(const std::string& target) const {
	print_string("makePresidentialPardonForm called");
    return new PresidentialPardonForm(target);
}
