# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: charlesleroy <charlesleroy@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/28 13:24:17 by noloupe           #+#    #+#              #
#    Updated: 2024/10/28 12:16:02 by charleslero      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	Cub3D

FILES		=	main.c\
				parsing/parsing.c\
				parsing/check_file.c\
				parsing/get_file_arr.c\
				parsing/trim_set.c\
				parsing/get_map_datas.c\
				parsing/treat_line.c\
				parsing/get_wall_texture.c\
				parsing/get_fc_color.c\
				parsing/get_map_arr.c\
				parsing/add_line_to_arr.c\
				parsing/fix_map.c\
				parsing/parse_map.c\
				utils/print_error_exit.c\
				utils/map_init.c\
				utils/free_map.c\
				utils/free_arr.c\
				utils/get_arr_size.c\
				utils/get_fc_color_utils.c\
				utils/fix_map_utils.c\
				utils/is_set.c\
				raycaster/body.c\
				raycaster/calculate_and_determine_wall_texture.c\
				raycaster/can_move.c \
				raycaster/draw_map2d.c \
				raycaster/draw_player.c \
				raycaster/go_through_screen.c \
				raycaster/init_player_starting_postion.c \
				raycaster/init_val_line_val.c \
				raycaster/key_press.c\
				raycaster/load_textures.c\
				raycaster/moves.c\
				raycaster/other_draw_player3D.c\
				raycaster/refresh_and_moves.c\
				raycaster/start_of_execution.c \
				tp/tp.c \
				raycaster/increment_one_degree.c\
				raycaster/go_through_screen_2.c\
				raycaster/ft_calculate_right_color.c\
				raycaster/ft_set_gen_rays_disv.c
				

SRCS		=	$(addprefix srcs/, $(FILES))
HEADERS		=	includes/*.h  # Remplacez par le bon chemin

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc -O3 -Os -flto -march=native -ffast-math

CFLAGS		=	-Wall -Werror -Wextra

SANITIZE	=	0

ifeq ($(SANITIZE), 1)
	CFLAGS	+= -g3 
endif

### LIB INCLUDES ###

LIBFT_DIR	=	srcs/libft
LIBFT		=	$(LIBFT_DIR)/libft.a

PRINTF_DIR	=	srcs/ft_printf
PRINTF		=	$(PRINTF_DIR)/libftprintf.a

GNL_DIR		=	srcs/gnl
GNL			=	$(GNL_DIR)/gnl.a

MLX_DIR		=	mini_lib/libx
MLX_LIB		=	-L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

DIRS		=	$(PRINTF) $(LIBFT) $(GNL)

CFLAGS		+= -I$(MLX_DIR)

### RULES ###

$(NAME):		$(OBJS)
				@echo "Compiling..."
				@echo "Making libft..."
				@make -C $(LIBFT_DIR)
				@echo "libft done."
				@echo "Making printf..."
				@make -C $(PRINTF_DIR)
				@echo "printf done."
				@echo "Making gnl..."
				@make -C $(GNL_DIR)
				@echo "gnl done."
				@$(CC) $(CFLAGS) $(OBJS) $(DIRS) $(MLX_LIB) -lreadline -o $(NAME)
				@echo "Compiling done."

%.o: %.c $(HEADERS)
				@$(CC) $(CFLAGS) -c $< -o $@
				
all:			$(NAME)

sanitize:		fclean
				@make SANITIZE=1

clean:
				@make clean -C $(LIBFT_DIR)
				@make clean -C $(PRINTF_DIR)
				@make clean -C $(GNL_DIR)
				@rm -f $(OBJS)

fclean:			clean
				@make fclean -C $(LIBFT_DIR)
				@make fclean -C $(PRINTF_DIR)
				@make fclean -C $(GNL_DIR)
				@rm -f $(NAME)

re :			fclean $(NAME)

.PHONY: sanitize all clean fclean re