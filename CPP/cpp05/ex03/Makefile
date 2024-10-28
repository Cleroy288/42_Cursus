NAME = Bureaucrat3

SRC = main.cpp Bureaucrat.cpp AForm.cpp PresidentialPardonForm.cpp RobotomyRequestForm.cpp ShrubberyCreationForm.cpp Intern.cpp

FLAGS = -Wall -Wextra -Werror -std=c++98 

all: $(NAME)

$(NAME):
	c++ $(FLAGS) $(SRC) -o $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all
