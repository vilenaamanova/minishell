/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 22:11:56 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/25 15:45:03 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_toenv(t_shell *val, char *str, int num)
{
	int		i;
	int		len;
	char	**new_env;

	i = 0;
	i = -1;
	if (arg_exist(val->envp_mod, str, num, i))
		return ;
	len = ft_len_str(val->envp_mod);
	new_env = malloc(sizeof(char *) * (len + 2));
	while (++i < len)
		new_env[i] = val->envp_mod[i];
	new_env[i++] = ft_strdup(str);
	new_env[i] = NULL;
	free(val->envp_mod);
	val->envp_mod = new_env;
}

void	add_toexpenv(t_shell *val, char *str, int num)
{
	int		i;
	int		len;
	char	**new_env;

	i = 0;
	if (num > 0 && arg_exist(val->envp_exp, str, num, i))
		return ;
	len = ft_len_str(val->envp_exp);
	while (val->envp_exp[i] && \
		ft_strnstr(val->envp_exp[i], str, ft_strlen(str)) == NULL)
		i++;
	if (i != len)
		return ;
	i = -1;
	new_env = malloc(sizeof(char *) * (len + 2));
	while (++i < len)
		new_env[i] = val->envp_exp[i];
	new_env[i++] = ft_strdup(str);
	new_env[i] = NULL;
	free(val->envp_exp);
	val->envp_exp = new_env;
}

void	add_envpxpenv(t_shell *shell, char *str)
{
	int	i;
	int	flag;

	if (ft_export_check(str))
		return ;
	i = -1;
	flag = 0;
	while (str[++i])
	{
		if (str[i] == '=')
		{
			flag = 1;
			break ;
		}
	}
	if (flag)
	{
		add_toenv(shell, str, i);
		add_toexpenv(shell, str, i);
	}
	else
		add_toexpenv(shell, str, 0);
}

void	expenv_sort(t_shell *shell)
{
	int			i;
	int			j;
	// int			size_env;
	char		**arr;
	t_envpmod	*tmp;

	i = 0;
	j = 0;
	tmp = shell->envp;
	while (tmp)
		i++;	
	arr = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (i < ft_len_str(shell->envp_exp) - 1)
	{ 
		j = i + 1;
		while (j < ft_len_str(shell->envp_exp))
		{
			if (ft_strcmp(shell->envp_exp[i], shell->envp_exp[j]))
			{
				envp = shell->envp_exp[i];
				shell->envp_exp[i] = shell->envp_exp[j];
				shell->envp_exp[j] = envp;
			}
			j++;
		}
	i++;
	}
	ft_print_env(shell->envp_exp);
}

void	ft_export(t_shell *shell, t_parser *cmd_pars)
{
	int			i;
	t_list		*tmp;

	i = 1;
	tmp = cmd_pars->cmd_list;
	if (cmd_pars->count == 1)
		expenv_sort(shell);
	else if ((cmd_pars->count > 1) && (tmp != NULL))
	{
		while (i < cmd_pars->count)
		{
			if (ft_strncmp((char *)tmp->content, "_=", 2)
				&& ft_strcmp((char *)tmp->content, "_"))
				add_envpxpenv(shell, (char *)tmp->content);
			tmp = tmp->next;
			i++;
		}
	}
	expenv_sort(shell);
}
