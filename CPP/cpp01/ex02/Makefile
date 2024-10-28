NAME = BRAIN  # changez ceci pour ce que vous voulez que votre exécutable soit nommé

SRC = main.cpp

FLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME):
	c++ $(FLAGS) $(SRC) -o $(NAME)

fclean:
	rm -f $(NAME)

re: clean all
