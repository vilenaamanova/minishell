/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:22:04 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/23 17:47:58 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, 256);
	if (!pwd)
	{
		free(pwd);
		printf("error: minishell: pwd\n");
		write (1, "\n", 1);
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
	exit (0);
}
