/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshelba <oshelba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 18:15:50 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/28 09:14:03 by oshelba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	error_exit(char *str)
{
	printf("%s\n", str);
	return (127);
}

int	ft_exit(t_shell *shell)
{
	int			num_arg;
	char		*arg;
	t_parser	*tmp_parser;

	num_arg = 0;
	tmp_parser = (t_parser *)shell->commands->content;
	if (!tmp_parser->cmd_list->content)
		return (127);
	if (tmp_parser->count == 1)
		return (0);
	if (tmp_parser->count > 2)
		return (error_exit("minishell: exit: too many arguments"));
	arg = (char *)tmp_parser->cmd_list->next->content;
	num_arg = ft_atoi(arg);
	if (ft_isdigit(num_arg))
		return (error_exit("minishell: exit: numeric argument required\n"));
	if (num_arg >= 0 && num_arg <= 255)
		shell->status = num_arg;
	else
		shell->status = num_arg % 256;
	return (0);
}
