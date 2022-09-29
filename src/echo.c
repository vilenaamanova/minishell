/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:17:02 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/28 19:31:48 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_echo(t_list *tmp)
{
	t_parser	*tmp_parser;
	t_list		*tmp_cmdlist;

	tmp_parser = (t_parser *)tmp->content;
	tmp_cmdlist = tmp_parser->cmd_list->next;
	while (tmp_cmdlist)
	{
		if (ft_strnstr("-n", (char *)tmp_cmdlist->content, 2))
			tmp_cmdlist = tmp_cmdlist->next;
		ft_putstr_fd(((char *)tmp_cmdlist->content), tmp_parser->fd_write);
		ft_putchar_fd(' ', tmp_parser->fd_write);
		tmp_cmdlist = tmp_cmdlist->next;
	}
}

void	ft_echo(t_shell *shell)
{
	int			flag_n;
	t_list		*tmp_next;
	t_parser	*parser;

	flag_n = 0;
	parser = (t_parser *)shell->commands->content;
	if (parser->fd_write <= 0)
		parser->fd_write = 1;
	tmp_next = parser->cmd_list->next;
	if (parser->cmd_list->content && tmp_next
		&& ft_strnstr("-n", (char *)tmp_next->content, 2))
	{
		flag_n = 1;
		ft_print_echo(shell->commands);
	}
	else if (tmp_next)
	{
		ft_print_echo(shell->commands);
		write(parser->fd_write, "\n", 1);
	}
	else if (!tmp_next)
		write(parser->fd_write, "\n", 1);
	if (parser->fd_write != 1)
		close(parser->fd_write);
}
