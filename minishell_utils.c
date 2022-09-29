/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 09:35:05 by ncathy            #+#    #+#             */
/*   Updated: 2022/07/27 09:35:05 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ispipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	else
		return (0);
}

int	ft_isoperator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (1);
	else
		return (0);
}

int	ft_isvalidstr(char c)
{
	if (ft_isspace(c) == 1)
		return (1);
	else
		return (0);
}
