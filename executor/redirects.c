/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:20:21 by ncathy            #+#    #+#             */
/*   Updated: 2022/09/26 14:30:49 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	find_limiter(char *cmd_line_lim)
{
	int		fd[2];
	pid_t	pid;
	char	*limiter;

	// if (pipe(fd) < 0)
	// 	error_mes2(ERROR_PIPE);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		limiter = get_next_line(0);
		while (limiter)
		{
			if (ft_strncmp(limiter, cmd_line_lim, ft_strlen(cmd_line_lim)) == 0)
				exit (0);
			free(limiter);
			limiter = get_next_line(0);
		}
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
}

void	ft_heredoc(t_shell *shell)
{
	char	*operator;
	char	*limiter;

	operator = shell->redirects->redir_write->redir_operator;
	limiter = shell->redirects->redir_write->file_name;
	if (ft_strncmp(operator, "<<", ft_strlen("<<")))
	{
		find_limiter(limiter);
	}
}