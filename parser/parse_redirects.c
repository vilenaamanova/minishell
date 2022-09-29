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

t_redirwrite	*ft_lstnew_rw(char *operator, char *file_name)
{
	t_redirwrite	*tmp;

	tmp = (t_redirwrite *)malloc(sizeof(t_redirwrite));
	if (!tmp)
		return (0);
	tmp->redir_operator = operator;
	tmp->file_name = file_name;
	tmp->next = NULL;
	return (tmp);
}

t_redirread	*ft_lstnew_rr(char *operator, char *file_name)
{
	t_redirread	*tmp;

	tmp = (t_redirread *)malloc(sizeof(t_redirread));
	if (!tmp)
		return (0);
	tmp->redir_operator = operator;
	tmp->file_name = file_name;
	tmp->next = NULL;
	return (tmp);
}

void	*get_redir_struct(t_shell *shell, char *token, char *next_to_redir)
{
	char	*file_name;
	char	*redir_operator;

	if (ft_strncmp(token, ">", ft_strlen(">")) == 0
		|| ft_strncmp(token, ">>", ft_strlen(">>")) == 0)
	{
		file_name = ft_strdup(next_to_redir);
		redir_operator = ft_strdup(token);
		ft_lstadd_back_rw(shell, ft_lstnew_rw(redir_operator, file_name));
	}
	if (ft_strncmp(token, "<", ft_strlen("<")) == 0
		|| ft_strncmp(token, "<<", ft_strlen("<<")) == 0)
	{
		file_name = ft_strdup(next_to_redir);
		redir_operator = ft_strdup(token);
		ft_lstadd_back_rr(shell, ft_lstnew_rr(redir_operator, file_name));
	}
	return (0);
}
