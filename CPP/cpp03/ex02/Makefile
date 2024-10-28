NAME = ClapTrap

SRC = main.cpp ClapTrap.cpp ScavTrap.cpp FragTrap.cpp

FLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME):
	c++ $(FLAGS) $(SRC) -o $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all