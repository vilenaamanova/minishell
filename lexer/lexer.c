/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:28:53 by ncathy            #+#    #+#             */
/*   Updated: 2022/07/12 11:28:53 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_token_length(char *str, int i)
{
	int	is_in_quote;
	int	token_length;

	is_in_quote = 0;
	token_length = 0;
	if (ft_isspace(str[i]) == 1)
	{
		while (ft_isspace(str[i]) == 1)
			i++;
	}
	if (ft_isvalidstr(str[i]) == 0 && check_qerror(str) == 0)
	{
		is_in_quote = check_quotes(str[i], is_in_quote);
		// if (is_in_quote == 1)
		// 	i++;
		while (str[i] != '\0'
			&& (ft_isvalidstr(str[i]) == 0 || (is_in_quote != 0)))
		{
			is_in_quote = check_quotes(str[i], is_in_quote);
			token_length++;
			i++;
		}
	}
	return (token_length);
}

void	split_the_string(char *str, t_list **tokens)
{
	int		i;
	int		token_length;
	char	*token;

	i = 0;
	token_length = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]) == 1)
		{
			while (ft_isspace(str[i]) == 1)
				i++;
		}
		token_length = get_token_length(str, i);
		token = ft_substr(str, i, token_length);
		ft_lstadd_back(tokens, ft_lstnew(token));
		i += token_length;
	}
}

t_list	*get_tokens(char *str)
{
	t_list	*tokens;

	tokens = NULL;
	split_the_string(str, &tokens);
	return (tokens);
}

void	lexer(char *str, t_shell *shell)
{
	create_envp_struct(shell);
	shell->tokens = get_tokens(str);
}
