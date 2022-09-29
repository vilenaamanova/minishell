/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 22:11:56 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/28 17:45:01 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exit_env(char *str)
{
	printf("%s\n", str);
	return (127);
}

int	find_ch(char *str, int flag)
{
	size_t	i;

	i = -1;
	while (++i < ft_strlen(str))
	{
		if (str[i] == '=')
		flag++;
	}
	return (flag);
}

void	add_envpxpenv(t_shell *shell, t_list *cmd)
{
	int		flag;
	char	*str;
	char	**arr;

	flag = 0;
	str = (char *)cmd->content;
	if (ft_export_check(str))
		return ;
	if (str[0] == '=')
		exit_env("not a valid identifier");
	flag = find_ch(str, flag);
	if (flag > 1)
		exit_env("bad math expression: operand expected at end of string");
	else if (flag == 1)
	{
		arr = NULL;
		arr = ft_split(str, '=');
		change_env(shell, arr[0], arr[1]);
		ft_free_arr(arr);
	}
	else
		change_env(shell, str, NULL);
	cmd = cmd->next;
}

void	expenv_sort(t_shell *shell)
{
	int			i;
	char		**arr;
	t_envpmod	*tmp;

	i = 0;
	tmp = shell->envp;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	arr = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	tmp = shell->envp;
	while (tmp)
	{
		arr[i] = ft_strjoin(tmp->variable, "=");
		arr[i] = ft_strjoin(arr[i], tmp->value);
		i++;
		tmp = tmp->next;
	}
	arr[i] = NULL;
	ft_sorting(arr);
	ft_print_env(arr);
	ft_free_arr(arr);
}

void	ft_export(t_shell *shell)
{
	int			i;
	t_list		*tmp_list;
	t_parser	*parser;

	i = 1;
	parser = (t_parser *)shell->commands->content;
	tmp_list = NULL;
	if (parser->cmd_list->next)
		tmp_list = parser->cmd_list->next;
	if (parser->count == 1)
		expenv_sort(shell);
	else if ((parser->count > 1) && (tmp_list != NULL))
	{
		while (tmp_list)
		{
			if (ft_strncmp((char *)tmp_list->content, "_=", 2)
				&& ft_strcmp((char *)tmp_list->content, "_"))
				add_envpxpenv(shell, tmp_list);
			tmp_list = tmp_list->next;
		}
	}
}
