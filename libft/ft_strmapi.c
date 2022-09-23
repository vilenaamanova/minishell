/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:09:03 by ncathy            #+#    #+#             */
/*   Updated: 2021/10/18 11:09:05 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*n;

	i = 0;
	if (!s || !f)
		return (NULL);
	n = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (n == NULL)
		return (NULL);
	if (s && f)
	{
		while (s[i])
		{
			n[i] = (*f)(i, s[i]);
			i++;
		}
	}
	n[i] = '\0';
	return (n);
}
