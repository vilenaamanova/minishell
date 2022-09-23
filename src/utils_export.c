/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 20:42:37 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/24 00:33:56 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	arg_exist(char **envp, char *str, int num, int i)
{
	char	*tmp;

	i = 0;
	tmp = ft_substr(str, 0, num + 1);
	while ((envp[i] && !ft_strnstr(envp[i], tmp, num + 1)))
		i++;
	free(tmp);
	if (envp[i] != NULL)
	{
		free(envp[i]);
		envp[i] = ft_strdup(str);
		return (1);
	}
	i = 0;
	tmp = ft_substr(str, 0, num);
	while ((envp[i] && !ft_strnstr(envp[i], tmp, num)))
		i++;
	free(tmp);
	if (envp[i] != NULL && (int)ft_strlen(envp[i]) == num)
	{
		free(envp[i]);
		envp[i] = ft_strdup(str);
		return (1);
	}
	return (0);
}

int	ft_export_check(char *envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_isalpha(envp[0]) && envp[0] != '0')
		{
			printf("export: `%s': not a valid identifier\n", envp);
			return (1);
		}
		if (!ft_isprint(envp[i]))
		{
			printf("export: `%s': not a valid identifier\n", envp);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_print_env(char **envp)
{
	int		i;
	char	**str;

	i = -1;
	while (envp[++i])
	{
		str = ft_split(envp[i], '=');
		write(1, "declare -x ", 11);
		write(1, str[0], ft_strlen(str[0]));
		if (ft_strchr(envp[i], '=') && !str[1])
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			write(1, "\"", 1);
		}
		else if (str[1])
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			write(1, ft_strchr(envp[i], '=') + 1, \
				ft_strlen(ft_strchr(envp[i], '=')) - 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
	}
}
