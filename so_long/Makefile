NAME = so_long

SRC = movement.c \
		so_long.c \
		pathfinding_and_parsing/ft_parsing.c \
		pathfinding_and_parsing/path_finding.c \
		create_map.c \
		handels_and_exit.c \
		collision_management.c \
		flip_and_resize.c \
		sub_images_and_counters.c \
		main.c \



OBJ = ${SRC:.c=.o}

CFLAGS = -Wall -Wextra -Werror -O3 -march=native -flto -ffast-math

%.o: %.c
	$(CC) -c $(CFLAGS) -I./lib -I./mini_lib/libx $< -o $@

LIB = ar rc $(NAME) ./mini_lib/libx/libmlx.a ./lib/libft.a

REMOVE = rm -f

DEPENDS = make -C ./lib

MLX = make -C ./mini_lib/libx

COMPILE = gcc $(CFLAGS) -o $(NAME) -I./lib -I./mini_lib/libx -L./lib -L./mini_lib/libx -lft -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

libft:
	$(DEPENDS)
	$(MLX)

$(NAME): libft $(OBJ)
	@$(COMPILE) $(OBJ)

clean:
	$(REMOVE) $(OBJ)
	make -C ./lib clean
	make -C ./mini_lib/libx clean

fclean: clean
	$(REMOVE) $(NAME)
	make -C ./lib fclean

re: fclean all

.PHONY: all clean fclean re
