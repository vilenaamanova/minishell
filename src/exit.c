/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:15:50 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/23 21:48:56 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(t_shell *shell)
{
	int		num_arg;
	char	*arg;

	num_arg = 0;
	if (!shell->parser->cmd_name)
		return (1);
	if (shell->parser->count == 0)
		return (0);
	if (shell->parser->count > 1)
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	arg = (char *)shell->parser->cmd_list->content;
	num_arg = ft_atoi(arg);
	if (!ft_isdigit(num_arg))
	{
		printf("minishell: exit: numeric argument required\n");
		return (1);
	}
	if (num_arg >= 0 && num_arg <= 255)
		shell->status = num_arg;
	else
		shell->status = num_arg % 256;
	return (0);
}
