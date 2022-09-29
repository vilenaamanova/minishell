/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshelba <oshelba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:11:48 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/27 10:59:22 by oshelba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_pr(t_envpmod *envp)
{
	if (!envp)
		return ;
	while (envp)
	{
		if (envp->value)
			printf("%s=%s\n", envp->variable, envp->value);
		envp = envp->next;
	}
	return ;
}
