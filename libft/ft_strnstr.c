/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 19:04:31 by ncathy            #+#    #+#             */
/*   Updated: 2022/07/14 16:57:50 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needle_len;

	i = 0;
	j = 0;
	needle_len = ft_strlen(needle);
	if (!needle_len)
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			while (haystack[i + j] == needle[j] && needle[j] != 0)
				j++;
			if (needle[j] == '\0' && (i + j) <= len)
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
