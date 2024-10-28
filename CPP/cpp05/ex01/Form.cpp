#include "Form.hpp"

Form::Form() : _name("DefaultForm"), _isSigned(false), _gradeRequiredToSign(150), _gradeRequiredToExecute(150) {
	print_string("default constructor called");
}

Form::Form(const std::string &name, int gradeRequiredToSign, int gradeRequiredToExecute)
    : _name(name), _isSigned(false), _gradeRequiredToSign(gradeRequiredToSign), _gradeRequiredToExecute(gradeRequiredToExecute) {
        if (_gradeRequiredToSign < 1 || _gradeRequiredToExecute < 1)
            throw GradeTooHighException();
        if (_gradeRequiredToSign > 150 || _gradeRequiredToExecute > 150)
            throw GradeTooLowException();
		print_string("constructor name grade to sign and to execute called");
}

Form::Form(const Form &src)
    : _name(src._name), _isSigned(src._isSigned), _gradeRequiredToSign(src._gradeRequiredToSign), _gradeRequiredToExecute(src._gradeRequiredToExecute) {
		if (_gradeRequiredToSign < 1 || _gradeRequiredToExecute < 1)
			throw GradeTooHighException();
		if (_gradeRequiredToSign > 150 || _gradeRequiredToExecute > 150)
			throw GradeTooLowException();
		print_string("copy constructor called");
	}

Form::~Form() {
	print_string("default destructor called");
}

Form &Form::operator=(const Form &rhs) {
    if (this != &rhs) {
        _isSigned = rhs._isSigned;
        // _name and _gradeRequiredTo* are const, so they cannot be copied
    }
	print_string("assignation operator called");
    return *this;
}

std::string Form::getName() const {
    return _name;
}

bool Form::isSigned() const {
    return _isSigned;
}

int Form::getGradeRequiredToSign() const {
    return _gradeRequiredToSign;
}

int Form::getGradeRequiredToExecute() const {
    return _gradeRequiredToExecute;
}

void Form::beSigned(const Bureaucrat &bureaucrat) {
    if (bureaucrat.getGrade() <= _gradeRequiredToSign) {
        _isSigned = true;
    } else {
        throw GradeTooLowException();
    }
	print_string("beSigned called");
}

std::ostream &operator<<(std::ostream &out, const Form &form) {
    out << "Form: " << form.getName() << ", is signed: ";
    
    if (form.isSigned()) {
        out << "yes";
    } else {
        out << "no";
    }
    out << ", grade required to sign: " << form.getGradeRequiredToSign()
        << ", grade required to execute: " << form.getGradeRequiredToExecute();
    return out;
}
