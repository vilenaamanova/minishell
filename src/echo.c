/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:17:02 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/24 00:30:37 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_echo(t_shell *shell, t_list *tmp)
{
	while (tmp->content && tmp->next)
	{
		ft_putstr_fd((char *)tmp->content, shell->fd_write);
		ft_putchar_fd(' ', shell->fd_write);
		if (tmp->next)
			tmp = tmp->next;
	}
	ft_putstr_fd((char *)tmp->content, shell->fd_write);
}

void	ft_echo(t_shell *shell)
{
	int			flag_n;
	t_list		*tmp;

	flag_n = 0;
	if (!shell->parser->cmd_list)
	{
		write(shell->fd_write, "\n", 1);
		return ;
	}
	tmp = shell->parser->cmd_list;
	if (tmp->content && tmp->next && ft_strnstr("-n", (char *)tmp->content, 2))
	{
			flag_n = 1;
			shell->parser->cmd_list = tmp->next;
			tmp = tmp->next;
	}
	ft_print_echo(shell, tmp);
	if (flag_n == 0)
		write(shell->fd_write, "\n", 1);
	if (shell->fd_write != 1)
		close(shell->fd_write);
}
