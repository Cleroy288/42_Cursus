#ifndef BUREAUCRAT
    #define BUREAUCRAT

#include <iostream>
#include <string>

class Form; 

class Bureaucrat {

    private:
        const std::string   _name;
        int                 _grade;

    public:
        Bureaucrat();
        Bureaucrat(const Bureaucrat &src);
        Bureaucrat(int grade);
        Bureaucrat(std::string name, int grade);
        Bureaucrat(std::string name);

        std::string getName() const;
        int getGrade() const;

        void Promotion();
        void dePromotion();
        void Print_stats();
        void signForm(Form &form);

        ~Bureaucrat();


    class GradeTooHighException : public std::exception {
    public:
        const char* what() const throw() {
            return "Grade too high";
        }
    };

    class GradeTooLowException : public std::exception {
    public:
        const char* what() const throw() {
            return "Grade too low";
        }
    };


};

void    print_string(std::string str);
std::ostream &operator<<(std::ostream &out, const Bureaucrat &bureaucrat);


#endif