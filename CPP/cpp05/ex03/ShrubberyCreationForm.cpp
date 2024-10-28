#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include <stdexcept>
#include <fstream>
#include <iostream>


ShrubberyCreationForm::ShrubberyCreationForm(const std::string &target)
    : AForm("Shrubbery Creation", 145, 137), _target(target) {
    print_string("constructor of ShrubberyCreationForm called");
}

std::string ShrubberyCreationForm::getTarget() const {
    return _target;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other)
    : AForm(other), _target(other._target) {
    std::cout << "ShrubberyCreationForm copy constructor called" << std::endl;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
    std::cout << "ShrubberyCreationForm destructor called" << std::endl;
}

void drawAsciiTree(const std::string& filename) {
    std::ofstream outfile(filename);

    if (!outfile.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    outfile << "       _-_" << std::endl;
    outfile << "    /~~   ~~\\" << std::endl;
    outfile << " /~~         ~~\\" << std::endl;
    outfile << "{               }" << std::endl;
    outfile << " \\  _-     -_  /" << std::endl;
    outfile << "   ~  \\\\ //  ~" << std::endl;
    outfile << "_- -   | | _- _" << std::endl;
    outfile << "  _ -  | |   -_" << std::endl;
    outfile << "      // \\\\" << std::endl;

    outfile.close();
}

void ShrubberyCreationForm::execute(Bureaucrat const &executor) const {
    if (!this->isSigned()) {
        throw NotSignedException();
    }
    else if (executor.getGrade() > this->getGradeRequiredToExecute()) {
        throw GradeTooLowException();
    }
    AForm::execute(executor);
    drawAsciiTree(this->_target + "_shrubbery");
}

