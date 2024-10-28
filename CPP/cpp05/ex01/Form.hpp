#ifndef FORM_HPP
#define FORM_HPP

#include "Bureaucrat.hpp"
#include <iostream>
#include <string>

class Bureaucrat;

class Form {
    private:
        const std::string _name;
        bool _isSigned;
        const int _gradeRequiredToSign;
        const int _gradeRequiredToExecute;

    public:
        Form();
        Form(const std::string &name, int gradeRequiredToSign, int gradeRequiredToExecute);
        Form(const Form &src);
        ~Form();

        Form &operator=(const Form &rhs);

        std::string getName() const;
        bool isSigned() const;
        int getGradeRequiredToSign() const;
        int getGradeRequiredToExecute() const;

        void beSigned(const Bureaucrat &bureaucrat);

        class GradeTooHighException : public std::exception {
            public:
                const char* what() const throw() {
                    return "Form::Grade too high";
                }
        };

        class GradeTooLowException : public std::exception {
            public:
                const char* what() const throw() {
                    return "Form::Grade too low";
                }
        };
};

std::ostream &operator<<(std::ostream &out, const Form &form);

#endif
