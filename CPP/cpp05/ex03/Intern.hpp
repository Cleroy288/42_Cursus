#ifndef INTERN_HPP
#define INTERN_HPP

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"
#include <string>

class Intern {
private:
    AForm* makeShrubberyCreationForm(const std::string& target) const;
    AForm* makeRobotomyRequestForm(const std::string& target) const;
    AForm* makePresidentialPardonForm(const std::string& target) const;
public:
    Intern();
    Intern(const Intern& other);
    Intern& operator=(const Intern& other);
    ~Intern();

    AForm* makeForm(const std::string& formName, const std::string& target) const;

};

#endif
