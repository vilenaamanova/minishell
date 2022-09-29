/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_envp_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 01:10:43 by ncathy            #+#    #+#             */
/*   Updated: 2022/09/24 01:10:43 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	part_of_key_envp(char c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return (1);
	else
		return (0);
}

int	get_arr_size(t_envpmod *envp)
{
	int			arr_size;
	t_envpmod	*tmp;

	arr_size = 0;
	tmp = envp;
	while (tmp)
	{
		if (tmp->variable && tmp->value)
			arr_size++;
		tmp = tmp->next;
	}
	return (arr_size);
}

char	**get_envp_arr_pt1(t_shell *shell)
{
	int			arr_size;
	char		**envp_arr;
	t_envpmod	*envp;

	if (!shell->envp)
		return (0);
	envp = shell->envp;
	arr_size = get_arr_size(shell->envp);
	if (!arr_size)
		return (0);
	envp_arr = (char **)malloc(sizeof(char *) * (arr_size + 1));
	get_envp_arr_pt2(envp, envp_arr);
	shell->envp_mod = envp_arr;
	return (envp_arr);
}

char	*get_value(char *variable, char **envp)
{
	int		i;
	int		len;
	char	*value;
	char	*envp_str;

	i = 0;
	variable = ft_strjoin(variable, "=");
	len = ft_strlen(variable);
	while (envp[i] && ft_strncmp(envp[i], variable, len))
		i++;
	envp_str = envp[i] + len;
	value = ft_substr(envp_str, 0, ft_strlen(envp_str));
	return (value);
}

char	*get_variable(char *token, int *start, int *end)
{
	char	*variable;

	while (part_of_key_envp(token[*end]) == 1)
		*end = *end + 1;
	variable = ft_substr(token, *start, *end - *start);
	return (variable);
}
