#include "Bureaucrat.hpp"

/*      -- UTILS --      */
/*************************/

void    print_string(std::string str) {
    std::cout<<str<<std::endl;
}

int is_valid_grade(int grade) {
    if (grade < 1)
        throw Bureaucrat::GradeTooHighException();
    else if (grade > 150)
        throw Bureaucrat::GradeTooLowException();

    return 0;
}

std::string Bureaucrat::getName() const {
    return _name;
}

int Bureaucrat::getGrade() const {
    return _grade;
}

void Bureaucrat::Print_stats() {
    print_string("Bureaucrat " + _name + " has grade " + std::to_string(_grade));
}

/*      -- UTILITIES --      */
/*****************************/

Bureaucrat::Bureaucrat() : _name("Noboddy") , _grade(150) {
    print_string("défault constructor called");
}

Bureaucrat::Bureaucrat(const Bureaucrat &src) : _name(src._name) {
    this->_grade = src._grade;
    print_string("Copy constructor called");
}

Bureaucrat::Bureaucrat(int grade) : _name("only_grade") {
    is_valid_grade(grade);
    this->_grade = grade;
    print_string("Constructor called with grade");
}

Bureaucrat::Bureaucrat(std::string name) : _name(name) , _grade(150) {
    print_string("Name constructor called");
}

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name) {
    is_valid_grade(grade);
    this->_grade = grade;
    print_string("Name and grade cnstructore called");
}

Bureaucrat::~Bureaucrat() {
    print_string("défault destructor called");
}

/*      -- CORPO FUNCTIONS --      */
/***********************************/

void Bureaucrat::Promotion() {
    if (_grade > 1) {
        _grade--;
        print_string("Bureaucrat named " + _name + " is promoted from grade " + std::to_string(_grade + 1) + " to grade " + std::to_string(_grade));
    } else {
        print_string("Bureaucrat " + _name + " is already at the highest grade (1) and cannot be promoted.");
        throw Bureaucrat::GradeTooHighException();
    }
}

void Bureaucrat::dePromotion() {
    if (_grade < 150) {
        _grade++;
        print_string("Bureaucrat named " + _name + " is demoted from grade " + std::to_string(_grade - 1) + " to grade " + std::to_string(_grade));
    } else {
        print_string("Bureaucrat " + _name + " is already at the lowest grade (150) and cannot be demoted.");
        throw Bureaucrat::GradeTooLowException();
    }
}

/*      -- OPERATOR --      */
/***********************************/

std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat) {
    out << bureaucrat.getName() << " bureaucrat is grade " << bureaucrat.getGrade();
    return out;
}