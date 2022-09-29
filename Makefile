NAME	=	minishell

SRCS	=	./lexer/check_quotes.c \
			./lexer/get_rid_quotes.c \
			./lexer/lexer.c \
			./lexer/run_envp.c \
			./lexer/run_envp_utils.c \
			./parser/get_char.c \
			./parser/parse_redirects.c \
			./parser/parse_redirects_utils.c \
			./parser/parser.c \
			./parser/parser_utils.c \
			./parser/syntax_error.c \
			./parser/parser_clear.c \
			./executor/executor_cmd.c \
			./executor/executor_utils.c \
			./executor/executor_utils_two.c \
			./executor/execute_read_redirs.c \
			./executor/execute_write_redirs.c \
			./src/cd.c \
			./src/echo.c \
			./src/env.c \
			./src/exit.c \
			./src/export.c \
			./src/pwd.c \
			./src/unset.c \
			./src/utils.c \
			./src/utils_export.c \
			./src/utils_export_two.c \
			signals.c \
			create_envp.c \
			create_envp_utils.c \
			minishell_utils.c \
			main.c \
			./get_next_line/get_next_line.c \
			./get_next_line/get_next_line_utils.c \
			
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