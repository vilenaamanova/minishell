/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 12:41:10 by ncathy            #+#    #+#             */
/*   Updated: 2022/04/22 12:41:10 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_line_read;

char	*rl_gets(void)
{
	if (g_line_read)
	{
		free(g_line_read);
		g_line_read = (char *) NULL;
	}
	g_line_read = readline("./minishell ");
	if (g_line_read && *g_line_read)
		add_history(g_line_read);
	return (g_line_read);
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->redirects = (t_redirects *)malloc(sizeof(t_redirects));
	if (!shell->redirects)
		return (NULL);
	shell->status = -1;
	shell->envp_arr = NULL;
	shell->envp_org = envp;
	shell->envp_mod = NULL;
	shell->envp_exp = NULL;
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->envp = NULL;
	shell->pipes = NULL;
	shell->redirects->redir_read = NULL;
	shell->redirects->redir_write = NULL;
	create_envp_struct(shell);
	return (shell);
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	set_param_tty(shell);
	sighandler_prepare(shell);
	while (1)
	{
		str = rl_gets();
		lexer(str, shell);
		parser(shell);
		if (shell->commands && executor(shell))
		{
			ft_lstclear(&shell->commands, free_parser_list);
			break ;
		}
		ft_lstclear(&shell->commands, free_parser_list);
	}
	free_shell(shell);
	unset_param_tty(shell);
}
