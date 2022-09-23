/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 01:05:24 by ncathy            #+#    #+#             */
/*   Updated: 2022/09/24 01:05:24 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirwrite	*ft_lstlast_rw(t_shell *shell)
{
	t_redirwrite	*tmp;

	tmp = shell->redirects->redir_write;
	if (tmp)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
	}
	return (tmp);
}

void	ft_lstadd_back_rw(t_shell *shell, t_redirwrite *new)
{
	if (shell->redirects->redir_write)
		ft_lstlast_rw(shell)->next = new;
	else
		shell->redirects->redir_write = new;
}

t_redirread	*ft_lstlast_rr(t_shell *shell)
{
	t_redirread	*tmp;

	tmp = shell->redirects->redir_read;
	if (tmp)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
	}
	return (tmp);
}

void	ft_lstadd_back_rr(t_shell *shell, t_redirread *new)
{
	if (shell->redirects->redir_read)
		ft_lstlast_rr(shell)->next = new;
	else
		shell->redirects->redir_read = new;
}
