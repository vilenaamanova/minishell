/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:49:23 by oshelba           #+#    #+#             */
/*   Updated: 2022/09/28 19:58:22 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fork_execve_cmd(t_shell *shell)
{
	int			pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell's error fork cmd");
		shell->status = 1;
	}
	else if (pid == 0)
		fork_execve_cmd_pt2(shell);
	waitpid(pid, &shell->status, 0);
	shell->status = shell->status / 256;
}

void	execute_cmd(t_parser *cmd, t_shell *shell)
{
	identify_redir_read(shell);
	identify_redir_write(shell);
	if (cmd->cmd_name && is_builtin_cmd(cmd->cmd_name))
		builtins_cmd(cmd, shell);
	else if (cmd->cmd_name && cmd->fd_read >= 0 && cmd->fd_write > 0)
	{
		fork_execve_cmd(shell);
		if (!isatty(cmd->fd_read))
			close(cmd->fd_read);
		if (!isatty(cmd->fd_write))
			close(cmd->fd_write);
	}
	if (!cmd->cmd_name && cmd->fd_read > 0)
		close(cmd->fd_read);
	if (!cmd->cmd_name && cmd->fd_write > 1)
		close(cmd->fd_write);
}

void	set_fd(t_list *commands, t_shell *shell)
{
	int			lst_size;
	int			pipe_fd[2];
	t_parser	*parser;

	lst_size = ft_lstsize(commands);
	while (commands)
	{
		parser = (t_parser *)commands->content;
		if (lst_size > 1 && commands->next)
			pipe(pipe_fd);
		if (shell->commands == commands)
			parser->fd_read = 0;
		if (commands->next)
			((t_parser *)commands->next->content)->fd_read = pipe_fd[0];
		if (!commands->next)
			parser->fd_write = 1;
		else
			parser->fd_write = pipe_fd[1];
		commands = commands->next;
	}
}

void	execute_list_cmds(t_shell *shell)
{
	t_parser	*cmd;

	set_fd(shell->commands, shell);
	while (shell->commands)
	{
		cmd = (t_parser *)shell->commands->content;
		execute_cmd(cmd, shell);
		shell->commands = shell->commands->next;
	}
}

int	executor(t_shell *shell)
{
	t_parser	*cmd;

	if (ft_lstsize(shell->commands) == 1)
	{
		cmd = (t_parser *)shell->commands->content;
		if (cmd->cmd_name
			&& !ft_strcmp(cmd->cmd_name, "exit"))
		{
			if (!ft_exit(shell))
				return (1);
		}
		else
			execute_list_cmds(shell);
	}
	else
		execute_list_cmds(shell);
	return (0);
}
