/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rid_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:35:04 by ncathy            #+#    #+#             */
/*   Updated: 2022/09/25 21:07:59 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_token_in_q_len(char *token)
{
	int	i;
	int	is_in_quote;
	int	token_length;
	
	i = 0;
	is_in_quote = 0;
	token_length = 0;
	while (token[i])
	{
		if (is_in_quote == 0 && ft_isquote(token[i]))
			is_in_quote = check_quotes(token[i], is_in_quote);
		else if (is_in_quote == 1 && ft_isquote(token[i]))
			is_in_quote = check_quotes(token[i], is_in_quote);
		else
			token_length++;	
		i++;
	}
	return (i);
}

void	get_rid_quotes(t_list *tokens)
{
	int		i;
	// int		quote_type;
	int		token_len;
	char	*token;

	i = 0;
	while (tokens)
	{
		token = (char *)tokens->content;
		token_len = get_token_in_q_len(token);
		tokens = tokens->next;
	}
}