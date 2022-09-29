/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 22:22:04 by alihandra         #+#    #+#             */
/*   Updated: 2022/09/28 11:28:53 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(0, 256);
	if (!pwd)
	{
		free(pwd);
		printf("error: minishell: pwd\n");
		write (1, "\n", 1);
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
