/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:24:19 by ncathy            #+#    #+#             */
/*   Updated: 2022/09/28 11:24:19 by ncathy           ###   ########.fr       */
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

typedef struct s_pipes {
	int					num_pipe;
	int					*pids;
	int					**pipes;
}	t_pipes;

typedef struct s_parser {
	int					fd_read;
	int					fd_write;
	int					count;
	char				*cmd_name;
	char				**cmd_args;
	t_list				*cmd_list;
}	t_parser;

typedef struct s_shell {
	int					status;
	char				**envp_arr;
	char				**envp_org;
	char				**envp_mod;
	char				**envp_exp;
	t_list				*tokens;
	t_list				*commands;
	t_envpmod			*envp;
	t_pipes				*pipes;
	t_redirects			*redirects;
	sigset_t			newset;
	t_termios			setting_tty;
	t_termios			setting_out_tty;
	struct sigaction	s_int;
	struct sigaction	s_quit;
}	t_shell;

	/* signals */

void					sigint_handler(int num);
void					sighandler_prepare(t_shell *shell);
void					set_param_tty(t_shell *shell);
void					unset_param_tty(t_shell *shell);

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
void					dollar_sign(t_list *tokens,
							char **envp);
void					dollar_sign_implement(char *token,
							char **ptoken, char **envp);
char					**get_envp_arr_pt1(t_shell *shell);
void					get_envp_arr_pt2(t_envpmod *envp, char **envp_arr);
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
char					**get_cmd_arr(t_list *cmd_list);
int						ft_strcmp(const char *s1, const char *s2);
void					free_parser_list(void *commands);
void					free_redirects(t_shell *shell);
void					free_shell(t_shell *shell);

	/* envp */

int						find_eq_sign(char *str);
void					create_envp_struct(t_shell *shell);
t_envpmod				*ft_lstnew_envpnode(char *variable, char *value);
t_envpmod				*ft_lstlast_envpnode(t_shell *shell);
void					ft_lstadd_back_envpnode(t_shell *shell, t_envpmod *new);

	/* commands */

void					ft_cd(t_parser *parser, t_shell *shell);
void					open_dir(t_shell *shell, char *str);
void					minicd(t_shell *shell, char *vars, char *str);
void					change_env(t_shell *shell, char *str, char *new_value);
void					ft_echo(t_shell *shell);
void					ft_print_echo(t_list *tmp);
void					env_pr(t_envpmod *envp);
int						ft_exit(t_shell *shell);
void					ft_export(t_shell *shell);
void					expenv_sort(t_shell *shell);
void					add_envpxpenv(t_shell *shell, t_list *cmd);
int						find_ch(char *str, int flag);
int						ft_pwd(void);
void					delete_env(t_shell *shell);
void					ft_free_envp(t_envpmod *tmp_envp);
int						check_name_unset(void *token);
void					ft_print_env(char **envp);
int						ft_export_check(char *envp);
int						arg_exist(char **envp, char *str, int num, int i);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strindex(char *str, char a);
char					**ft_sorting(char **arr);
void					ft_free_arr(char **s);
t_envpmod				*get_my_env(t_envpmod *env, char *name);
int						ft_len_str(char **str);
int						lst_add_back_env(t_shell *shell, t_envpmod *new);
t_envpmod				*lst_new_env(char *name, char *content);
t_envpmod				*get_env_key(t_envpmod *env, char *key);

	/* executor */

int						executor(t_shell *shell);
void					execute_list_cmds(t_shell *shell);
void					set_fd(t_list *commands, t_shell *shell);
void					execute_cmd(t_parser *cmd, t_shell *shell);
void					fork_execve_cmd(t_shell *shell);
void					fork_execve_cmd_pt2(t_shell *shell);
int						**init_pipes(int pipes_amount);
char					*get_patch_cmd(char *cmd_name, t_shell *shell);
char					**ft_find_paths(char *envp[]);
char					*ft_find_cmd(char *cmd, char *paths[]);
int						is_builtin_cmd(char *cmd_name);
void					builtins_cmd(t_parser *parser, t_shell *shell);
char					*ft_strjoin_f(char *s1, char *s2, int need_free);
void					strjoin_cleaner(char *s1, char *s2, int need_free);
void					identify_redir_read(t_shell *shell);
int						determine_fd_read(t_redirread *r_read, int fd_read);
int						ft_heredoc(int fd_write, char *eof);
void					identify_redir_write(t_shell *shell);
int						determine_fd_write(t_redirwrite *r_write, int fd_write);

	/* utils */

t_shell					*init_shell(char **envp);
char					*get_next_line(int fd);
char					*ft_strchr(const char *s, int c);
char					*ft_strjoin_mod(char *s1, char *s2);

	/* handle prompt */

char					*rl_gets(void);
int						main(int argc, char **argv, char **envp);

void					find_builtin(t_shell *shell);

#endif