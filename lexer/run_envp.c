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

void	get_envp_arr(t_envpmod *envp, char **envp_arr)
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

void	dollar_sign_implement(char *token, char **envp)
{
	int		i;
	int		j;
	int		is_in_quote;
	int		quote_type;
	char	*value;
	char	*variable;

	i = 0;
	is_in_quote = 0;
	while (token[i])
	{
		is_in_quote = check_quotes(token[i], is_in_quote);
		if (is_in_quote == 1)
		{
			quote_type = identify_quote_type(token[i]);
			i++;
		}
		if (token[i] == '$' && quote_type != 1 && token[i + 1])
		{
			i++;
			j = i;
			value = NULL;
			variable = NULL;
			if (ft_isdigit(token[j]) && token[j] == '?')
				j++;
			
			/* exit status */

			// if (token[j] == '?')
			//

			if (part_of_key_envp(token[j]))
			{
				variable = get_variable(token, &i, &j);
				value = get_value(variable, envp);
			}
		}
	}
}

void	dollar_sign(t_list *tokens, char **envp)
{
	char	*token;

	while (tokens)
	{
		token = tokens->content;
		dollar_sign_implement(token, envp);
		tokens = tokens->next;
	}
}
