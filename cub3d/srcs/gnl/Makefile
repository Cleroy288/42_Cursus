NAME		=	gnl.a

SRCS		=	get_next_line.c\
				get_next_line_utils.c\

SRCS_BONUS	=	get_next_line_bonus.c\
				get_next_line_utils_bonus.c\

OBJS		=	$(SRCS:.c=.o)

OBJS_BONUS	=	$(SRCS_BONUS:.c=.o)

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

all:			$(NAME)

$(NAME):		$(OBJS)
				@ar -rc $(NAME) $(OBJS)

bonus:			all $(OBJS_BONUS)
				@ar -rc $(NAME) $(OBJS-BONUS)

.c.o:
				@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

clean:
				@rm -f $(OBJS) $(OBJS_BONUS)

fclean:			clean
				@rm -f $(NAME)

re:				fclean all

.PHONY:			all bonus clean fclean re
