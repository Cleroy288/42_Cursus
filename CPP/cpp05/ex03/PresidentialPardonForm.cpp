#include "PresidentialPardonForm.hpp"
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include <iostream>

PresidentialPardonForm::PresidentialPardonForm() : AForm("Presidential Pardon", 25, 5), _target("Default") {
    print_string("default constructor of PresidentialPardonForm called");
}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target)
    : AForm("Presidential Pardon", 25, 5), _target(target) {
        print_string("constructor of PresidentialPardonForm called");
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other)
    : AForm(other), _target(other._target) {
        print_string("copy constructor of PresidentialPardonForm called");
}

PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other) {
    if (this != &other) {
        AForm::operator=(other);
    }
    return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {
    print_string("destructor of PresidentialPardonForm called");
}

void PresidentialPardonForm::execute(Bureaucrat const &executor) const {
    if (!this->isSigned())
		throw NotSignedException();
    if (executor.getGrade() > this->getGradeRequiredToExecute())
        throw GradeTooLowException();
    AForm::execute(executor);
    std::cout << _target << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}

std::string PresidentialPardonForm::getTarget() const {
    return _target;
}
