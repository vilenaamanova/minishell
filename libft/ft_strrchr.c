/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:04:50 by ncathy            #+#    #+#             */
/*   Updated: 2021/10/09 12:30:25 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;

	i = ft_strlen(s);
	while (*(unsigned char *)s && i)
	{
		if (*(unsigned char *)(s + i) == (unsigned char )c)
			return ((char *)(s + i));
		i--;
	}
	if (*(unsigned char *)(s + i) == (unsigned char )c)
		return ((char *)(s + i));
	return (NULL);
}
