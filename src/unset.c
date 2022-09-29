/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshelba <oshelba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 20:35:32 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/28 10:04:35 by oshelba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_name_unset(void *token)
{
	char	*str;
	int		i;

	str = (char *)token;
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (1);
	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i])
			&& str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	ft_free_envp(t_envpmod *tmp_envp)
{
	t_envpmod	*tmp_envp_free;

	tmp_envp_free = tmp_envp->next;
	tmp_envp->next = tmp_envp->next->next;
	if (tmp_envp_free->value)
		free(tmp_envp_free->value);
	if (tmp_envp_free->variable)
		free(tmp_envp_free->variable);
	free(tmp_envp_free);
	tmp_envp_free = NULL;
}

void	delete_env(t_shell *shell)
{
	t_list		*tmp_list_com;
	t_parser	*tmp_parser;
	t_envpmod	*tmp_envp;

	tmp_parser = (t_parser *)shell->commands->content;
	tmp_list_com = tmp_parser->cmd_list;
	if (tmp_list_com->next)
	{
		tmp_list_com = tmp_list_com->next;
		while (tmp_list_com)
		{
			tmp_envp = shell->envp;
			while (tmp_envp != NULL && tmp_envp->next != NULL)
			{
				if (ft_strcmp((char *)tmp_list_com->content, \
					tmp_envp->next->variable) == 0)
					ft_free_envp(tmp_envp);
				tmp_envp = tmp_envp->next;
			}
			tmp_list_com = tmp_list_com->next;
		}
	}
}
