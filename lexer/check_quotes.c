/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 10:46:22 by ncathy            #+#    #+#             */
/*   Updated: 2022/08/18 10:46:22 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_type(char c)
{
	if (ft_isquote(c) == 1 && c == '\'')
		return (1);
	else if (ft_isquote(c) && c == '"')
		return (2);
	return (0);
}

int	check_quotes(char c, int is_in_quote)
{
	if (ft_isquote(c) == 1 && is_in_quote == 0)
		return (1);
	else if (ft_isquote(c) == 1 && is_in_quote == 1)
		return (0);
	else if (ft_isquote(c) == 0 && is_in_quote == 1)
		return (1);
	else if (ft_isquote(c) == 0 && is_in_quote == 0)
		return (0);
	return (0);
}

int	check_qerror(char *str)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (str[i] != '\0')
	{
		if (ft_isquote(str[i]) == 1)
			quote_count++;
		i++;
	}
	if (quote_count % 2 == 1)
	{
		perror ("minishell: syntax error near unexpected token 'quoting'");
		return (1);
	}
	return (0);
}
