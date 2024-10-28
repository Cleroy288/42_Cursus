NAME = pipex

SRC = main.c \
		ft_set_args_in_struct.c \
		ft_free_what_u_give_me.c \
		get_path.c \
		close_parent_and_children.c \
		ft_child_process.c \
		ft_init_and_execute_process.c \
		ft_dup2_and_close.c \

OBJ = ${SRC:.c=.o}

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

LIB = lib/libft.a

REMOVE = rm -f

COMPILE = gcc $(CFLAGS) -o $(NAME) -I ./lib -L. $(LIB)

all: $(NAME)

$(NAME): $(OBJ)
	make -C lib
	@$(COMPILE) $(OBJ) -L. $(LIB)

%.o: %.c
	$(CC) -c $(CFLAGS) -I./lib -o $@ $<

clean:
	$(REMOVE) $(OBJ)
	make -C ./lib clean

fclean: clean
	$(REMOVE) $(NAME)
	make -C ./lib fclean

re: fclean all

.PHONY: all clean fclean re