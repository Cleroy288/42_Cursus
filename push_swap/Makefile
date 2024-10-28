NAME = push_swap

SRC = main.c \
	parsing/ft_set_argv_in_str.c \
	ft_free_and_exit.c \
	parsing/split_check_and_fulfill_stack_a.c \
	algo/ft_radix.c \
	algo/ft_verif_sort.c \
	algo/quicksort_for_little_stack.c \
	operations_ch/ra_rb_rra.c \
	operations_ch/sa_sb_pb_pa.c\
	ft_change_val_to_tab_rank.c \
	ft_nb_of_nb.c


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

