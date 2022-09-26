/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:41:23 by ncathy            #+#    #+#             */
/*   Updated: 2022/04/22 12:41:23 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>
# include <termios.h>

# define BUFFER_SIZE 10

typedef struct termios	t_termios;

typedef struct s_envpmod {
	char				*variable;
	char				*value;
	struct s_envpmod	*next;
}	t_envpmod;

typedef struct s_redirread {
	char				*file_name;
	char				*redir_operator;
	struct s_redirread	*next;
}	t_redirread;

typedef struct s_redirwrite {
	char				*file_name;
	char				*redir_operator;
	struct s_redirwrite	*next;
}	t_redirwrite;

typedef struct s_redirects {
	char				*operator;
	struct s_redirread	*redir_read;
	struct s_redirwrite	*redir_write;
}	t_redirects;

typedef struct s_parser {
	int					count;
	char				*cmd_name;
	t_list				*cmd_list;
	// struct s_parser		*next; //возможно убрать
}	t_parser;

typedef struct s_shell {
	int					status;
	int					fd_read;
	int					fd_write;
	char				**envp_arr;
	char				**envp_org; //копия
	// char				**envp_mod; //проверить где сидит
	char				**envp_exp;
	t_list				*tokens;
	t_list				*commands;
	// t_parser			*parser;
	t_envpmod			*envp;
	t_redirects			*redirects;
	sigset_t			newset;
	t_termios			setting_tty;
	t_termios			setting_out_tty;
	struct sigaction	s_int;
	struct sigaction	s_quit;
	struct s_pipes		*pipes;
}	t_shell;

typedef struct s_pipes {
	int					num_pipe;
	int					*pids;
	int					**pipes;
}	t_pipes;

/* lexer */
void					lexer(char *str, t_shell *shell);
t_list					*get_tokens(char *str, char **envp);
void					split_the_string(char *str, t_list **tokens);
int						ft_isquote(char c);
int						identify_quote_type(char c);
void					get_rid_quotes(t_list *tokens);
int						get_token_in_q_len(char *token);
char					*get_token(char *token, int token_length);
int						ft_isoperator(char c);
int						ft_isvalidstr(char c);
int						check_quotes(char c, int is_in_quote);
int						check_qerror(char *str);
void					dollar_sign(t_list *tokens, char **envp);
void					dollar_sign_implement(char *token, char **envp);
void					get_envp_arr(t_envpmod *envp, char **envp_arr);
char					*get_variable(char *token, int *start, int *end);
char					*get_value(char *variable, char **envp);
int						part_of_key_envp(char c);

/* parser */
void					parser(t_shell *shell);
int						is_operator_token(char *token);
int						is_pipe_token(char *token);
int						is_redirects_token(char *token);
int						check_all_tokens(t_list *tokens);
int						check_first_token(char *first_token);
int						check_last_token(char *last_token);
int						check_redirects(char *token, char *next_to_redir);
int						check_two_char_in_a_row(char *token, char *next_token);
int						syntax_error(t_list *tokens);
void					*get_redir_struct(t_shell *shell,
							char *token, char *next_to_redir);
t_redirwrite			*ft_lstlast_rw(t_shell *shell);
void					ft_lstadd_back_rw(t_shell *shell, t_redirwrite *new);
t_redirread				*ft_lstlast_rr(t_shell *shell);
void					ft_lstadd_back_rr(t_shell *shell, t_redirread *new);
t_parser				*init_parser(void);
void					get_cmd_struct(t_parser *parser, char *token);
void					get_cmd(t_shell *shell, t_list **tokens_list);

/* envp */
int						find_eq_sign(char *str);
void					create_envp_struct(t_shell *shell);
t_envpmod				*ft_lstnew_envpnode(char *variable, char *value);
t_envpmod				*ft_lstlast_envpnode(t_shell *shell);
void					ft_lstadd_back_envpnode(t_shell *shell, t_envpmod *new);

/* commands */
void					change_env(t_shell *shell, char *str, char *new_value);
void					minicd(t_shell *shell, char *vars, char *str);
void					open_dir(t_shell *shell, char *str);
void					ft_cd(t_parser *parser, t_shell *shell);
void					ft_print_echo(t_shell *shell, t_list *tmp);
void					ft_echo(t_shell *shell);
void					env_pr(t_envpmod *envp);
int						ft_exit(t_shell *shell);
void					add_toenv(t_shell *val, char *str, int num);
void					add_toexpenv(t_shell *val, char *str, int num);
void					add_envpxpenv(t_shell *shell, t_list *cmd);
void					expenv_sort(t_shell *shell);
void					ft_export(t_shell *shell);
void					ft_pwd(void);
int						check_name_unset(void *token);
void					delete_env(t_shell *shell, t_parser *parser);
int						ft_strcmp(const char *s1, const char *s2);
int						arg_exist(char **envp, char *str, int num, int i);
int						ft_export_check(char *envp);
void					ft_print_env(char **envp);
t_envpmod				*get_env_key(t_envpmod *env, char *key);
t_envpmod				*lst_new_env(char *name, char *content);
int						lst_add_back_env(t_shell *shell, t_envpmod *new);
int						ft_len_str(char **str);

/* signals */
void					sigint_handler(int num);
void					sighandler_prepare(t_shell *shell);
void					set_param_tty(t_shell *shell);
void					unset_param_tty(t_shell *shell);

/* utils */
t_shell					*init_shell(char **envp);
char					*get_next_line(int fd);
char					*ft_strchr(const char *s, int c);
char					*ft_strjoin_mod(char *s1, char *s2);

/* handle prompt */
char					*rl_gets(void);

int						main(int argc, char **argv, char **envp);

/* executor */
int						executor(t_shell *shell);
int						handle_error_code(t_shell *shell);

void					find_builtin(t_shell *shell);

#endif