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

char	*get_value(char *variable, char **envp)
{
	int		i;
	int		len;
	// char	*value;
	char	*envp_str;

	i = 0;
	variable = ft_strjoin(variable, "=");
	len = ft_strlen(variable);
	while (envp[i] && ft_strncmp(envp[i], variable, len))
		i++;
	envp_str = envp[i] + len;

	printf("ENVP STR:\n");
	printf("%s\n", envp_str);

	return (variable);
}

char	*get_variable(char *token, int *start, int *end)
{
	char	*variable;

	while (part_of_key_envp(token[*end]) == 1)
		*end = *end + 1;
	variable = ft_substr(token, *start, *end - *start);
	return (variable);
}
