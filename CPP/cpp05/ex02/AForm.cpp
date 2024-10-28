#include "AForm.hpp"

AForm::AForm() : _name("DefaultForm"), _isSigned(false), _gradeRequiredToSign(150), _gradeRequiredToExecute(150) {
	print_string("default constructor called");
}

AForm::AForm(const std::string &name, int gradeRequiredToSign, int gradeRequiredToExecute)
    : _name(name), _isSigned(false), _gradeRequiredToSign(gradeRequiredToSign), _gradeRequiredToExecute(gradeRequiredToExecute) {
        if (_gradeRequiredToSign < 1 || _gradeRequiredToExecute < 1)
            throw GradeTooHighException();
        if (_gradeRequiredToSign > 150 || _gradeRequiredToExecute > 150)
            throw GradeTooLowException();
		print_string("constructor name grade to sign and to execute called");
}

AForm::AForm(const AForm &src)
    : _name(src._name), _isSigned(src._isSigned), _gradeRequiredToSign(src._gradeRequiredToSign), _gradeRequiredToExecute(src._gradeRequiredToExecute) {
		if (_gradeRequiredToSign < 1 || _gradeRequiredToExecute < 1)
			throw GradeTooHighException();
		if (_gradeRequiredToSign > 150 || _gradeRequiredToExecute > 150)
			throw GradeTooLowException();
		print_string("copy constructor called");
	}

AForm::~AForm() {
	print_string("default destructor called");
}

AForm &AForm::operator=(const AForm &rhs) {
    if (this != &rhs) {
        _isSigned = rhs._isSigned;
    }
	print_string("assignation operator called");
    return *this;
}

std::string AForm::getName() const {
    return _name;
}

bool AForm::isSigned() const {
    return _isSigned;
}

int AForm::getGradeRequiredToSign() const {
    return _gradeRequiredToSign;
}

int AForm::getGradeRequiredToExecute() const {
    return _gradeRequiredToExecute;
}

void AForm::beSigned(const Bureaucrat &bureaucrat) {
    if (bureaucrat.getGrade() <= _gradeRequiredToSign) {
        _isSigned = true;
    } else {
        throw GradeTooLowException();
    }
	print_string("beSigned called");
}

std::ostream &operator<<(std::ostream &out, const AForm &form) {
    out << "AForm: " << form.getName() << ", is signed: ";
    if (form.isSigned()) {
        out << "yes";
    } else {
        out << "no";
    }
    out << ", grade required to sign: " << form.getGradeRequiredToSign()
        << ", grade required to execute: " << form.getGradeRequiredToExecute();
    return out;
}

void AForm::execute(Bureaucrat const &executor) const {
    if (!_isSigned) {
        throw AForm::NotSignedException();
    }

    if (executor.getGrade() > _gradeRequiredToExecute) {
        throw AForm::GradeTooLowException();
    }

}
