#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"
#include <cstdlib> // Pour rand()
#include "Bureaucrat.hpp"

class RobotomyRequestForm : public AForm {
private:
    const std::string _target;

public:
	RobotomyRequestForm();
    RobotomyRequestForm(const std::string &target);
    RobotomyRequestForm(const RobotomyRequestForm &other);
    RobotomyRequestForm &operator=(const RobotomyRequestForm &other);
    virtual ~RobotomyRequestForm();

    virtual void execute(Bureaucrat const &executor) const;
    virtual std::string getTarget() const ;
};

#endif
