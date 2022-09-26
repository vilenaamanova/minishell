/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 22:11:56 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/26 11:11:14 by ncathy           ###   ########.fr       */
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

/*
t_envpmod	*find_envp(t_envpmod *envp, char *new)
{
	t_envpmod *tmp;

	tmp = envp;
	while (tmp)
	{
		if (ft_strncmp(tmp->variable, new, ft_strlen(new) + 1))//проверяем совпадение
			return(tmp->variable);
		tmp->next;
	}*/
	/*if (arg_exist(val->envp_mod, str, num, i))
		return ;
	len = ft_len_str(val->envp_mod);
	new_env = malloc(sizeof(char *) * (len + 2));
	while (++i < len)
		new_env[i] = val->envp_mod[i];
	new_env[i++] = ft_strdup(str);
	new_env[i] = NULL;
	free(val->envp_mod);
	val->envp_mod = new_env;*/
	//return (envp);
//}
/*
void	add_toexpenv(t_shell *val, char *str, int num, int flag)
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
}*/

int	ft_strindex(char *str, char a)
{
	unsigned int	i;

	i = 0;
	while (str[i] && str[i] != a)
		i++;
	if (i < ft_strlen(str))
		return (i);
	else
		return (-1);
}

void	add_envpxpenv(t_shell *shell, t_list *cmd)
{
	size_t	i;
	int	flag;
	char *str;
	//t_envpmod *new;
	char *re_envp;//после =

	while (cmd)
	{
		str = (char *)cmd->content;
		if (ft_export_check(str))
			return ;
		i = -1;
		flag = 0;
		if (str[0] == '=')// если начинается с = то ошибка
			{printf("not a valid identifier"); return ;}//ft_error("not a valid identifier");// отработать ошибки
		while (++i < ft_strlen(str))// ищем в строчке =
		{
			if (strcmp(str, "=") == 0)
				flag = 1;
		}
		if (!ft_strnstr(str, "=", ft_strlen(str)))
			change_env(shell, str, NULL);
		else
		{
			re_envp = ft_substr(str, 0, ft_strindex(str, '='));
			change_env(shell, re_envp, 
				ft_strdup(ft_strnstr(str, "=", ft_strlen(str) + 1)));
			free (re_envp);
		}
		/*new = NULL;
		new = get_my_env(shell->envp, str);
		if (new)// если существует переменная, то меняем значение
		{
			if (new->value)
				free(new->value);
			new->value = ft_strdup(str);
			return ;
		}
		else// если нет, то в конец добавляем новый лист
			change_env(shell, str);*/
		//add_toenv(shell cmd, get_my_env(shell->envp, str), i, flag);//get_my_env возвращает  envpmod
		cmd = cmd->next;
	}
}

char	**ft_sorting(char **arr)
{
	int i;
	int j;
	char *tmp;
	
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

void	expenv_sort(t_shell *shell)
{
	int		i;
	//int		size_env;
	char	**arr;
	t_envpmod *tmp;

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

	parser = (t_parser *)shell->commands->content;

	i = 1;
	tmp_list = NULL;
	if (parser->cmd_list->next)
		tmp_list = parser->cmd_list->next;// пропускаем первый аргумент export
	shell->status = 0;
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
	expenv_sort(shell);
}
