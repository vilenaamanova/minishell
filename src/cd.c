/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 17:53:42 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/23 21:46:57 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_env(t_shell *shell, char *str, char *new_value)
{
	t_envpmod	*tmp;

	tmp = get_env_key(shell->envp, str);
	if (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		tmp->value = new_value;
	}
	else
		lst_add_back_env(shell, lst_new_env(ft_strdup(str), new_value));
}

void	minicd(t_shell *shell, char *vars, char *str)
{
	char		*path;
	char		*pwd;
	t_envpmod	*envp;

	envp = get_env_key(shell->envp, str);
	path = envp->value;
	if (!path)
	{
		printf("minishell: cd: %s not set\n", str);
		shell->status = 1;
		return ;
	}
	chdir(path);
	change_env(shell, "OLDPWD", vars);
	pwd = getcwd(0, 1000);
	change_env(shell, "PWD", pwd);
	change_env(shell, "_", ft_strdup("cd"));
	if ((ft_strnstr("OLDPWD", str, 6)) != NULL)
		ft_pwd();
	return ;
}

void	open_dir(t_shell *shell, char *str)
{
	DIR		*dir;
	char	*oldpwd;
	char	*pwd;

	dir = opendir(str);
	if (!dir)
	{
		printf("minishell: cd: ");
		printf ("%s: %s\n", str, strerror(errno));
	}
	else
	{
		closedir(dir);
		oldpwd = getcwd(0, 1000);
		chdir(str);
		change_env(shell, "OLDPWD", oldpwd);
		pwd = getcwd(0, 1000);
		change_env(shell, "PWD", pwd);
		change_env(shell, "_", ft_strdup("cd"));
	}
}

void	ft_cd(t_shell *shell)
{
	char	*vars;

	vars = NULL;
	vars = getcwd(vars, 1000);
	if (shell->parser->count > 1)
		printf("minishell: cd: too many arguments\n");
	else if (shell->parser->count == 0 || \
		ft_strncmp(shell->parser->cmd_list->content, "~", 2) == 0)
		minicd(shell, vars, "HOME");
	else if (shell->parser->count > 0 && \
		ft_strncmp(shell->parser->cmd_list->content, "-", 2) == 0)
		minicd(shell, vars, "OLDPWD");
	else
		open_dir(shell, vars);
	free(vars);
}
