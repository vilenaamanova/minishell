/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 20:39:28 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/23 21:53:23 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envpmod	*get_env_key(t_envpmod *env, char *key)
{
	t_envpmod	*lst;

	if (!env)
		return (0);
	lst = env;
	while (lst)
	{
		if ((ft_strnstr(key, lst->variable, ft_strlen(key)))
			&& (ft_strlen(key) == ft_strlen(lst->variable)))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

t_envpmod	*lst_new_env(char *name, char *content)
{
	t_envpmod	*lst;

	lst = malloc(sizeof(t_envpmod));
	if (!lst)
		return (0);
	lst->variable = name;
	lst->value = content;
	lst->next = NULL;
	return (lst);
}

int	lst_add_back_env(t_shell *shell, t_envpmod *new)
{
	t_envpmod	*begin;

	if (new == NULL)
		return (1);
	if (shell->envp == NULL)
		shell->envp = new;
	else
	{
		begin = shell->envp;
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = new;
	}
	return (0);
}

int	ft_len_str(char **str)
{
	int	len;

	len = 0;
	if (str)
	{
		while (str[len])
			len++;
	}
	return (len);
}
