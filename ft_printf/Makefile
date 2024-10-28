SRCS = ft_putmem.c \
		utils_basic.c \
		ft_putnbr_base.c \
		ft_putnbr_u.c \
		ft_printf.c \
		ft_putnbr.c \

OBJS = $(SRCS:.c=.o)

NAME = libftprintf.a
CC = gcc
FLAGS = -Wall -Werror -Wextra
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean
