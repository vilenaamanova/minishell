/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 16:50:48 by ncathy            #+#    #+#             */
/*   Updated: 2022/08/17 16:50:48 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_operator_token(char *token)
{
	if (is_pipe_token(token) == 0 || is_redirects_token(token) == 0)
		return (0);
	return (1);
}

int	is_pipe_token(char *token)
{
	if (ft_strncmp("|", token, ft_strlen(token)))
		return (0);
	return (1);
}

int	is_redirects_token(char *token)
{
	if (ft_strncmp(">", token, ft_strlen(token))
		|| ft_strncmp("<", token, ft_strlen(token))
		|| ft_strncmp(">>", token, ft_strlen(token))
		|| ft_strncmp("<<", token, ft_strlen(token)))
		return (0);
	return (1);
}
