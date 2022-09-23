/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 14:11:48 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/24 00:30:50 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_pr(t_shell *shell, t_envpmod *envp)
{
	shell->status = 0;
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
