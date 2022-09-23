/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:09:32 by ncathy            #+#    #+#             */
/*   Updated: 2021/10/18 11:09:34 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	str_len;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	str_len = ft_strlen(s);
	if (str_len < len)
		len = str_len;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
	{
		str[i] = '\0';
		return (str);
	}
	while (i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
