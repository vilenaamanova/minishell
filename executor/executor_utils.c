/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 00:32:30 by oshelba           #+#    #+#             */
/*   Updated: 2022/09/28 19:27:15 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_find_cmd(char *cmd, char *paths[])
{
	char	*path;
	int		i;

	i = 0;
	if (!paths)
		return (0);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin_f(path, cmd, 1);
		if (access(path, F_OK) == 0)
		{
			free(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_arr(paths);
	return (NULL);
}

char	**ft_find_paths(char *envp[])
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (0);
}

char	*get_patch_cmd(char *cmd_name, t_shell *shell)
{
	char	*path;

	if (access(cmd_name, F_OK) == 0 && access(cmd_name, X_OK) == 0)
		path = cmd_name;
	else
		path = ft_find_cmd(cmd_name, ft_find_paths(shell->envp_mod));
	if (!path || access(path, X_OK) == -1)
	{
		printf ("minishell: %s: command not found\n", cmd_name);
		free(path);
		exit (1);
	}
	return (path);
}

int	**init_pipes(int pipes_amount)
{
	int	i;
	int	**res;

	i = 0;
	res = (int **)malloc(sizeof(int *) * (pipes_amount + 1));
	if (!res)
	{
		printf("Error: pipe");
		return (NULL);
	}
	while (i < pipes_amount)
	{
		res[i] = (int *)malloc(sizeof(int) * 2);
		if (!res[i])
			return (NULL);
		if (pipe(res[i]) < 0)
			return (NULL);
		i++;
	}
	return (res);
}
