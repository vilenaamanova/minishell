/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_read_redirs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:20:21 by ncathy            #+#    #+#             */
/*   Updated: 2022/09/28 20:10:51 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_heredoc(int fd_write, char *eof)
{
	int		pid;
	char	*limiter;

	pid = fork();
	if (pid == 0)
	{
		ft_putstr_fd("heredoc> ", 1);
		limiter = get_next_line(0);
		while (limiter)
		{
			if (ft_strncmp(limiter, eof, ft_strlen(eof)) == 0)
				exit (0);
			free (limiter);
			ft_putstr_fd("heredoc> ", 1);
			limiter = get_next_line(0);
		}
	}
	close(fd_write);
	waitpid(pid, NULL, 0);
	return (0);
}

int	determine_fd_read(t_redirread *r_read, int fd_read)
{
	int		new_fd_read;
	char	*operator;
	char	*file_name;

	new_fd_read = -1;
	operator = ft_strdup(r_read->redir_operator);
	file_name = ft_strdup(r_read->file_name);
	if (fd_read != 0 && fd_read != -1)
		close(fd_read);
	new_fd_read = open(file_name, O_RDONLY, 0644);
	return (new_fd_read);
}

void	identify_redir_read(t_shell *shell)
{
	int			pipe_heredoc[2];
	t_parser	*parser;
	t_redirread	*r_read;

	parser = (t_parser *)shell->commands->content;
	r_read = shell->redirects->redir_read;
	while (r_read)
	{
		if (ft_strncmp(r_read->redir_operator, "<", ft_strlen("<")) == 0)
			parser->fd_read = determine_fd_read(r_read, parser->fd_read);
		else if (ft_strncmp(r_read->redir_operator, "<<", ft_strlen("<<")) == 0)
		{
			if (parser->fd_read != 0 && parser->fd_read != -1)
				close(parser->fd_read);
			pipe(pipe_heredoc);
			parser->fd_read = pipe_heredoc[0];
			if (ft_heredoc(pipe_heredoc[1], r_read->file_name))
			{
				close(pipe_heredoc[0]);
				parser->fd_read = -1;
			}
		}
		r_read = r_read->next;
	}
}
