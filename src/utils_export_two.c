/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshelba <oshelba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 09:55:12 by oshelba           #+#    #+#             */
/*   Updated: 2022/09/28 09:55:24 by oshelba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envpmod	*get_my_env(t_envpmod *env, char *name)
{
	t_envpmod	*lst;

	if (!env)
		return (0);
	lst = env;
	while (lst)
	{
		if (ft_strnstr(name, lst->variable, ft_strlen(name))
			&& (ft_strlen(name) == ft_strlen(lst->variable)))
			return (lst);
		lst = lst->next;
	}
	return (0);
}

void	ft_free_arr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return ;
}

char	**ft_sorting(char **arr)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[j])
		{
			if (ft_strcmp(arr[i], arr[j]) < 0)
			{
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (arr);
}
