/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:58:41 by ncathy            #+#    #+#             */
/*   Updated: 2022/09/14 16:58:41 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_envpmod	*ft_lstnew_envpnode(char *variable, char *value)
{
	t_envpmod	*tmp;

	tmp = (t_envpmod *)malloc(sizeof(t_envpmod));
	if (!tmp)
		return (0);
	tmp->variable = variable;
	tmp->value = value;
	tmp->next = NULL;
	return (tmp);
}

t_envpmod	*ft_lstlast_envpnode(t_shell *shell)
{
	t_envpmod	*tmp;

	tmp = shell->envp;
	if (tmp)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
	}
	return (tmp);
}

void	ft_lstadd_back_envpnode(t_shell *shell, t_envpmod *new)
{
	if (shell->envp != NULL)
		ft_lstlast_envpnode(shell)->next = new;
	else
		shell->envp = new;
}
