NAME = philo

SRC = main.c \
	utils.c \
	init.c \
	routine.c \

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

REMOVE = rm -f

COMPILE = $(CC) $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJ)
	@$(COMPILE) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(REMOVE) $(OBJ)

fclean: clean
	$(REMOVE) $(NAME)

re: fclean all

.PHONY: all clean fclean re
