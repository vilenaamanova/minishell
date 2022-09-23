/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:05:55 by ncathy            #+#    #+#             */
/*   Updated: 2021/10/18 11:05:59 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_numlen(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static char	*ft_arr(char *str, unsigned int nbr, long int i)
{
	while (nbr > 0)
	{
		str[i--] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	char			*str;
	long int		i;

	i = ft_numlen(n);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		nbr = n * -1;
		str[0] = '-';
	}
	else
		nbr = n;
	str = ft_arr(str, nbr, i);
	return (str);
}
