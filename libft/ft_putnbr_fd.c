/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:06:51 by ncathy            #+#    #+#             */
/*   Updated: 2021/10/18 11:06:53 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_neg(int n, int fd)
{
	write(fd, "-", 1);
	n = -n;
	ft_putnbr_fd(n, fd);
	return (n);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else
	{
		if (n < 0)
			is_neg(n, fd);
		else if (n < 10)
		{
			c = n + '0';
			write(fd, &c, 1);
		}
		else if (n >= 10)
		{
			ft_putnbr_fd(n / 10, fd);
			c = n % 10 + '0';
			write(fd, &c, 1);
		}
	}
}
