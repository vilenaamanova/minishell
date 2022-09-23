/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 20:35:32 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/24 00:33:17 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_name_unset(void *token)
{
	char	*str;
	int		i;

	str = (char *)token;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i])
			&& str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	delete_env(t_shell *shell, t_list *token)
{
	t_envpmod	*lst;
	t_envpmod	*tmp;

	lst = get_env_key(shell->envp, (char *)token->content);
	if (!shell->envp || !lst)
		return ;
	if (lst == shell->envp)
	{
		shell->envp = shell->envp->next;
		if (lst->value)
			free(lst->value);
		free(lst->variable);
		free(lst);
	}
	else
	{
		tmp = shell->envp;
		while (tmp->next != lst)
			tmp = tmp->next;
		tmp->next = lst->next;
		if (lst->value)
			free(lst->value);
		free(lst->variable);
		free(lst);
	}
}
