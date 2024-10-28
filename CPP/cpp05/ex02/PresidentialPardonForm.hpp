#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"
#include <string>

class PresidentialPardonForm : public AForm {
    private:
        std::string _target;

    public:
        PresidentialPardonForm();
        PresidentialPardonForm(const std::string &target);
        PresidentialPardonForm(const PresidentialPardonForm &other);
        virtual ~PresidentialPardonForm();

        PresidentialPardonForm &operator=(const PresidentialPardonForm &other);

        virtual void execute(Bureaucrat const &executor) const;

		std::string getTarget() const ;

};

#endif
