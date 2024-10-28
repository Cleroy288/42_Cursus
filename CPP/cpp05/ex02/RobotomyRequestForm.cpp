#include "RobotomyRequestForm.hpp"
#include <iostream>
#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm()
    : AForm("Robotomy Request default", 72, 45), _target("def target") {
        print_string("def constructor of RobotomyRequestForm called");
}

// Assurez-vous que votre constructeur utilise la signature correcte du constructeur de AForm
RobotomyRequestForm::RobotomyRequestForm(const std::string &target)
    : AForm("Robotomy Request", 72, 45), _target(target) {
        print_string("constructor of RobotomyRequestForm called");
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other)
    : AForm(other), _target(other._target) {
        print_string("copy constructor of RobotomyRequestForm called");
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
    AForm::operator=(other);
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {
    print_string("destructor of RobotomyRequestForm called");
}

void RobotomyRequestForm::execute(Bureaucrat const &executor) const {
/*
    const int _gradeRequiredToSign;
    const int _gradeRequiredToExecute;

    • RobotomyRequestForm: Required grades: sign 72, exec 45
    Makes some drilling noises. Then, informs that <target> has been robotomized
    successfully 50% of the time. Otherwise, informs that the robotomy failed
*/
	if (!this->isSigned()) {
		throw NotSignedException();
    }
    else if (executor.getGrade() > this->getGradeRequiredToExecute()) {
        throw GradeTooLowException();
    }
    AForm::execute(executor);
    std::cout << "Drilling noises... ";
    if (rand() % 2) {
        std::cout << this->getTarget() << " has been robotomized successfully." << std::endl;
    } else {
        print_string("Robotomy failed");
    }
}

std::string RobotomyRequestForm::getTarget() const {
    return _target;
}