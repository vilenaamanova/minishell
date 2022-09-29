/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 16:38:49 by ncathy            #+#    #+#             */
/*   Updated: 2022/08/20 16:38:49 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_cmd_arr(t_list *cmd_list)
{
	int		i;
	int		lst_len;
	char	**cmd_arr;

	cmd_arr = NULL;
	lst_len = ft_lstsize(cmd_list);
	if (lst_len)
	{
		i = 0;
		cmd_arr = (char **)malloc(sizeof(char *) * (lst_len + 1));
		if (!cmd_arr)
			return (NULL);
		while (cmd_list)
		{
			cmd_arr[i] = ft_strdup((char *)cmd_list->content);
			cmd_list = cmd_list->next;
			i++;
		}
		cmd_arr[lst_len] = NULL;
	}
	return (cmd_arr);
}
