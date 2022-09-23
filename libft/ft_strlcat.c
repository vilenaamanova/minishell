/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 18:59:37 by ncathy            #+#    #+#             */
/*   Updated: 2021/10/08 19:00:42 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	j = dst_len;
	if (dstsize <= j)
		return (dstsize + src_len);
	if (dstsize != 0 && j < dstsize)
	{
		while (src[i] && i < dstsize - j - 1)
		{
			dst[j + i] = src[i];
			i++;
		}
		dst[j + i] = '\0';
	}
	return (dst_len + src_len);
}
