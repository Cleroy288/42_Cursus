#ifndef AFORM_HPP
#define AFORM_HPP

#include "Bureaucrat.hpp"
#include <iostream>
#include <string>

class Bureaucrat;

class AForm {
protected:

private:
    const std::string _name;
    bool _isSigned;
    const int _gradeRequiredToSign;
    const int _gradeRequiredToExecute;

public:
    virtual void execute(Bureaucrat const &executor) const = 0; // Fonction purement virtuelle
    virtual std::string getTarget() const = 0;


    AForm();
    AForm(const std::string &name, int gradeRequiredToSign, int gradeRequiredToExecute);
    AForm(const AForm &src);
    virtual ~AForm();

    AForm &operator=(const AForm &rhs);

    std::string getName() const;
    bool isSigned() const;
    int getGradeRequiredToSign() const;
    int getGradeRequiredToExecute() const;

    void beSigned(const Bureaucrat &bureaucrat);

    //std::string getTarget() const;

    bool			getSigned( void ) const;


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

    class NotSignedException : public std::exception {
        public:
            const char* what() const throw() {
                return "Form is not signed";
        }
    };

};

std::ostream &operator<<(std::ostream &out, const AForm &form);

#endif // AFORM_HPP
