# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chleroy <chleroy@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/19 16:04:20 by hubrygo           #+#    #+#              #
#    Updated: 2023/09/20 13:45:35 by chleroy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c \
	chained_list_functions.c \
	builtin.c \
	builtin_utils.c \
	signal_handler.c \
	cd.c \
	child.c \
	env.c \
	free.c \
	parent.c \
	pars.c \
	pars_utils.c \
	pipe.c \
	pwd.c \
	utils.c \
	ft_chained_list.c \
	set_arg_for_echo.c \
	set_arg_for_echo_utils.c \
	extract_input_outputfile.c \
	free_functions.c \
	dup_and_close.c \
	extract_word.c \
	signal_handler_utils.c \
	exec_command.c \
	execute_process.c \
	here_doc.c \
	check_validity.c \
	skip_to_next_quotes.c \
	set_command_for_echo.c \
	process_and_dispach.c \
	init_first_part.c \
	init_second_part.c \
	chained_list_functions_utils.c \
	chained_list_utils.c \
	free_functions_first_part.c \
	free_functions_second_part.c \
	split_on_spaces.c \
	ft_len.c \
	set_word.c \
	special_split.c \
	get_env_var_name.c \
	export.c \
	export_second_part.c \
	str_without_one_lettre.c \
	set_variable_in_str.c \
	quotes.c \
	get_right_command.c \
	initialise.c

OBJ_DIR = OBJ
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIB = lib/libft.a

READLINELIB = -lreadline

REMOVE = rm -f

COMPILE = gcc $(CFLAGS) -o $(NAME) -I ./lib -L. $(LIB) $(READLINELIB)

LDFLAGS		= -L/${HOME}/.brew/opt/readline/lib
CPPFLAGS	= -I/${HOME}/.brew/opt/readline/include

all: $(NAME)

$(NAME): $(OBJ)
	make -C lib
	$(COMPILE) $(OBJ) ${LDFLAGS} ${CPPFLAGS} -L. $(LIB)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $(CFLAGS) ${CPPFLAGS} -I./lib -o $@ $<

clean:
	$(REMOVE) $(OBJ)
	make -C ./lib clean

fclean: clean
	$(REMOVE) -r $(OBJ_DIR)
	$(REMOVE) $(NAME)
	make -C ./lib fclean

re: fclean all

.PHONY: all clean fclean re
