/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 16:23:35 by ncathy            #+#    #+#             */
/*   Updated: 2022/09/14 16:23:35 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_eq_sign(char *str)
{
	int	k;

	k = 0;
	while (str[k] != '=')
		k++;
	return (k);
}

void	create_envp_struct(t_shell *shell)
{
	int		i;
	int		index_of_eq_sign;
	char	*variable;
	char	*value;

	i = 0;
	while (shell->envp_org[i])
	{
		index_of_eq_sign = find_eq_sign(shell->envp_org[i]);
		variable = ft_substr(shell->envp_org[i], 0, index_of_eq_sign);
		value = ft_substr(shell->envp_org[i], index_of_eq_sign + 1,
				ft_strlen(shell->envp_org[i]));
		ft_lstadd_back_envpnode(shell, ft_lstnew_envpnode(variable, value));
		i++;
	}
}
