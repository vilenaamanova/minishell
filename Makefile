NAME	=	minishell

SRCS	=	./lexer/lexer.c \
			./lexer/lexer_utils.c \
			./lexer/check_quotes.c \
			./lexer/get_rid_quotes.c \
			./lexer/run_envp.c \
			./lexer/run_envp_utils.c \
			./parser/get_char.c \
			./parser/parse_pipes.c \
			./parser/parse_redirects_utils.c \
			./parser/parse_redirects.c \
			./parser/parser_utils.c \
			./parser/parser.c \
			./parser/syntax_error.c \
			create_envp.c \
			create_envp_utils.c \
			minishell_utils.c \
			main.c \
			signals.c \
			./get_next_line/get_next_line.c \
			./get_next_line/get_next_line_utils.c \
			# ./src/export.c
			# ./src/unset.c
			# ./executor/executor_cmd.c
			# ./src/echo.c
			# ./src/cd.c \
			# ./src/env.c \
			# ./src/exit.c \
			# ./src/pwd.c \
			# ./src/utils_export.c \
			# ./src/utils.c \
			# prov.c \

LIBFT	=	./libft/libft.a

HEADER	=	minishell.h

OBJ		=	$(patsubst %.c, %.o, $(SRCS))

CC		=	cc

CFLAGS	=	-g -Wall -Wextra -Werror 

RFLAGS	=	-lreadline 

.PHONY	:	all clean fclean re

all 	:	$(NAME)

$(NAME)	: 	$(OBJ) $(HEADER)
		@$(MAKE) -C libft/ --silent
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(RFLAGS) -o $(NAME)
		
%.o	: %.c	$(HEADER)
	$(CC)	$(CFLAGS) -c $< -o $@

clean	:
	@rm -f $(OBJ)
	@$(MAKE) clean -C libft/

fclean	:	clean
	@rm $(NAME)
	@$(MAKE) fclean -C libft/

re		:	fclean all