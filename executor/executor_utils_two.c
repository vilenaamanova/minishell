/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:34:59 by oshelba           #+#    #+#             */
/*   Updated: 2022/09/28 19:58:15 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fork_execve_cmd_pt2(t_shell *shell)
{
	char		*path;
	t_parser	*cmd;

	while (shell->commands)
	{
		cmd = (t_parser *)shell->commands->content;
		dup2(cmd->fd_read, 0);
		dup2(cmd->fd_write, 1);
		path = get_patch_cmd(cmd->cmd_name, shell);
		sigaction(SIGQUIT, &shell->s_quit, NULL);
		if (shell->status == -9)
			exit(9);
		if (execve(path, cmd->cmd_args, shell->envp_mod) < 0)
			perror("Command execution error");
		shell->commands = shell->commands->next;
	}
}

void	strjoin_cleaner(char *s1, char *s2, int need_free)
{
	if (need_free == 1)
		free (s1);
	else if (need_free == 2)
		free (s2);
	else if (need_free == 3)
	{
		free (s1);
		free (s2);
	}
}

char	*ft_strjoin_f(char *s1, char *s2, int need_free)
{
	char	*dest;
	char	*p;
	void	*tmp;
	void	*tmp2;

	tmp = (void *)s1;
	tmp2 = (void *)s2;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	p = dest;
	while (s1 && *s1 != '\0')
		*dest++ = *s1++;
	while (s2 && *s2 != '\0')
		*dest++ = *s2++;
	*dest++ = '\0';
	strjoin_cleaner(tmp, tmp2, need_free);
	return (p);
}

void	builtins_cmd(t_parser *parser, t_shell *shell)
{
	char	*cmd;

	if (parser->cmd_list)
	{
		cmd = (char *)parser->cmd_list->content;
		if (ft_strncmp("cd", cmd, ft_strlen(cmd) + 1) == 0)
			ft_cd(parser, shell);
		if (ft_strncmp("pwd", cmd, ft_strlen(cmd) + 1) == 0)
			ft_pwd();
		if (ft_strncmp("env", cmd, ft_strlen(cmd) + 1) == 0)
			env_pr(shell->envp);
		if (ft_strncmp("export", cmd, ft_strlen(cmd) + 1) == 0)
			ft_export(shell);
		if (ft_strncmp("unset", cmd, ft_strlen(cmd) + 1) == 0)
			delete_env(shell);
		if (ft_strncmp("exit", cmd, ft_strlen(cmd) + 1) == 0)
			ft_exit(shell);
		if (ft_strncmp("echo", cmd, ft_strlen(cmd) + 1) == 0)
			ft_echo(shell);
	}
}

int	is_builtin_cmd(char *cmd_name)
{
	if (!ft_strcmp(cmd_name, "cd")
		|| !ft_strcmp(cmd_name, "pwd")
		|| !ft_strcmp(cmd_name, "env")
		|| !ft_strcmp(cmd_name, "echo")
		|| !ft_strcmp(cmd_name, "export")
		|| !ft_strcmp(cmd_name, "unset")
		|| !ft_strcmp(cmd_name, "exit"))
	{
		return (1);
	}
	return (0);
}
