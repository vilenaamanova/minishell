/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rid_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 19:35:04 by ncathy            #+#    #+#             */
/*   Updated: 2022/09/25 22:00:08 by ncathy           ###   ########.fr       */
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
	return (token_length);
}

char	*get_token(char *token, int token_length)
{
	int		i;
	int		j;
	int		is_in_quote;
	char	*noq_token;

	i = 0;
	j = 0;
	is_in_quote = 0;
	noq_token = (char *)malloc(sizeof(char) * (token_length + 1));
	while (token[i] != '\0')
	{
		if (is_in_quote == 0 && ft_isquote(token[i]))
			is_in_quote = check_quotes(token[i], is_in_quote);
		else if (is_in_quote == 1 && ft_isquote(token[i]))
			is_in_quote = check_quotes(token[i], is_in_quote);
		else
		{
			noq_token[j] = token[i];
			j++;	
		}
		i++;
	}
	return (noq_token);
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
		tokens->content = get_token(token, token_len);

		// printf("TOKEN LEN WITHOUT QUOTES:\n");
		// printf("%d\n", token_len);
		
		tokens = tokens->next;
	}
}