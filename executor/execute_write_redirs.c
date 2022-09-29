/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_write_redirs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:31:56 by ncathy            #+#    #+#             */
/*   Updated: 2022/09/28 20:10:47 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	determine_fd_write(t_redirwrite *r_write, int fd_write)
{
	int		new_fd_write;
	char	*operator;
	char	*file_name;

	new_fd_write = -1;
	operator = ft_strdup(r_write->redir_operator);
	file_name = ft_strdup(r_write->file_name);
	if (ft_strncmp(operator, ">", ft_strlen(">")) == 0
		|| ft_strncmp(operator, ">>", ft_strlen(">>")) == 0)
	{
		if (fd_write != 1 && fd_write != -1)
			close(fd_write);
		if (ft_strncmp(operator, ">", ft_strlen(">")) == 0)
			new_fd_write = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (ft_strncmp(operator, ">>", ft_strlen(">>")) == 0)
			new_fd_write = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
		return (new_fd_write);
	}
	return (new_fd_write);
}

void	identify_redir_write(t_shell *shell)
{
	t_parser		*parser;
	t_redirwrite	*r_write;

	parser = (t_parser *)shell->commands->content;
	r_write = shell->redirects->redir_write;
	while (r_write)
	{
		parser->fd_write = determine_fd_write(r_write, parser->fd_write);
		r_write = r_write->next;
	}
}
