/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 01:11:01 by ncathy            #+#    #+#             */
/*   Updated: 2022/09/24 01:11:01 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	join_strings(char **ptoken, char *pt1, char *pt2, char *value)
{
	if (!value)
	{
		if (!pt1 && !pt2)
			*ptoken = ft_strdup("");
		if (!pt1 && pt2)
			*ptoken = pt1;
		if (pt1 && !pt2)
			*ptoken = pt2;
		if (pt1 && pt2)
			*ptoken = ft_strjoin(pt1, pt2);
	}
	else
	{
		if (!pt1 && !pt2)
			*ptoken = value;
		if (pt1 && !pt2)
			*ptoken = ft_strjoin(pt1, value);
		if (!pt1 && pt2)
			*ptoken = ft_strjoin(value, pt2);
		if (pt1 && pt2)
		{
			*ptoken = ft_strjoin(pt1, value);
			*ptoken = ft_strjoin(*ptoken, pt2);
		}
	}
}

void	replace_with_envp(char **ptoken, int start, int end, char *value)
{
	int		token_len;
	char	*pt1;
	char	*pt2;

	pt1 = NULL;
	pt2 = NULL;
	token_len = ft_strlen(*ptoken);
	if (start)
		pt1 = ft_substr(*ptoken, 0, start);
	if (token_len - end - 1)
		pt2 = ft_substr(*ptoken, end + 1, token_len - end - 1);
	join_strings(ptoken, pt1, pt2, value);
}

void	get_envp_arr_pt2(t_envpmod *envp, char **envp_arr)
{
	int		i;
	char	*tmp;

	i = 0;
	while (envp)
	{
		if (envp->value)
		{
			tmp = ft_strjoin(envp->variable, "=");
			envp_arr[i] = ft_strjoin(tmp, envp->value);
			free (tmp);
			i++;
		}
		envp = envp->next;
	}
	envp_arr[i] = NULL;
}

void	dollar_sign_implement(char *token,
		char **ptoken, char **envp)
{
	int		i;
	int		j;
	int		is_in_quote;
	char	*value;

	i = 0;
	is_in_quote = 0;
	while (token[i++])
	{
		is_in_quote = check_quotes(token[i], is_in_quote);
		if (is_in_quote == 1)
			i++;
		if (token[i] != '\'' && token[i] == '$' && token[i + 1])
		{
			j = ++i;
			value = NULL;
			if (ft_isdigit(token[j]) && token[j] == '?')
				j++;
			if (part_of_key_envp(token[j]))
				value = get_value(get_variable(token, &i, &j), envp);
			replace_with_envp(ptoken, i - 1, j - 1, value);
			token = *ptoken;
			i = 0;
		}
	}
}

void	dollar_sign(t_list *tokens, char **envp)
{
	char	*token;
	char	**ptoken;

	while (tokens)
	{
		token = tokens->content;
		ptoken = (char **) &tokens->content;
		dollar_sign_implement(token, ptoken, envp);
		tokens = tokens->next;
	}
}
