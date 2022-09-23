/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 01:06:09 by ncathy            #+#    #+#             */
/*   Updated: 2022/09/24 01:06:09 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*get_redir_struct(t_shell *shell, char *token, char *next_to_redir)
{
	t_redirread		*new_redir_read;
	t_redirwrite	*new_redir_write;

	new_redir_read = (t_redirread *)malloc(sizeof(t_redirread));
	if (!new_redir_read)
		return (NULL);
	new_redir_write = (t_redirwrite *)malloc(sizeof(t_redirwrite));
	if (!new_redir_write)
		return (NULL);
	if (ft_strncmp("<", token, ft_strlen(token)) == 0
		|| ft_strncmp("<<", token, ft_strlen(token)) == 0)
	{
		new_redir_write->file_name = ft_strdup(next_to_redir);
		new_redir_write->redir_operator = ft_strdup(token);
		ft_lstadd_back_rw(shell, new_redir_write);
	}
	if (ft_strncmp(">", token, ft_strlen(token)) == 0
		|| ft_strncmp(">>", token, ft_strlen(token)) == 0)
	{
		new_redir_read->file_name = ft_strdup(next_to_redir);
		new_redir_read->redir_operator = ft_strdup(token);
		ft_lstadd_back_rr(shell, new_redir_read);
	}
	return (0);
}
