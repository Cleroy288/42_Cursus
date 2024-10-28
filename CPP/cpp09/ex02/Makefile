NAME = PmergeMe

SRC = main.cpp PmergeMe.cpp

FLAGS = -Wall -Wextra -Werror -std=c++98 -Ofast -ffast-math -march=native

all: $(NAME)

$(NAME):
	c++ $(FLAGS) $(SRC) -o $(NAME)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all
