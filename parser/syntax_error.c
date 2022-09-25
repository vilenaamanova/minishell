/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 17:25:47 by ncathy            #+#    #+#             */
/*   Updated: 2022/08/17 17:25:47 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_first_token(char *first_token)
{
	if (is_pipe_token(first_token) == 1)
	{
		ft_putstr_fd("lalala1 minishell: syntax error near unexpected token '|'\n", 2);
		return (1);
	}
	return (0);
}

int	check_last_token(char *last_token)
{
	if (is_redirects_token(last_token) == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token 'newline'\n", 2);
		return (1);
	}
	return (0);
}

int	check_redirects(char *token, char *next_to_redir)
{
	if (is_redirects_token(token))
	{
		if (is_pipe_token(next_to_redir) == 1)
		{
			ft_putstr_fd("lalala2 minishell: syntax error near unexpected token '|'\n", 2);
			return (1);
		}
		else if (is_redirects_token(next_to_redir) == 1)
		{
			perror("minishell: syntax error near unexpected token ''"); // исправить
			return (1);
		}
	}
	return (0);
}

int	check_two_char_in_a_row(char *token, char *next_token)
{
	if (is_operator_token(token) == 1 && is_operator_token(next_token) == 1)
	{
		perror("minishell: syntax error near unexpected token ''"); // исправить
		return (1);
	}
	return (0);
}

int	syntax_error(t_list *tokens)
{
	char	*token;
	char	*next_token;
	char	*first_token;
	char	*last_token;

	first_token = tokens->content;
	last_token = ft_lstlast(tokens)->content;
	if (check_first_token(first_token) == 1
		|| check_last_token(last_token) == 1)
		return (1);
	while (tokens)
	{
		token = tokens->content;
		if (tokens->next != NULL)
		{
			next_token = tokens->next->content;
			if (check_redirects(token, next_token) == 1
				|| check_two_char_in_a_row(token, next_token) == 1)
				return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}
