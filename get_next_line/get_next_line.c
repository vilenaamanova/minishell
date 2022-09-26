/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:31:35 by ncathy            #+#    #+#             */
/*   Updated: 2022/09/26 13:30:32 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_check_for_errors(int fd)
{
	if (BUFFER_SIZE <= 0 || fd < 0)
		return ((void) NULL);
}

static void	ft_null_and_return(char *line)
{
	if (!line)
		return ((void) NULL);
}

static char	*ft_get_line(char *line)
{
	int		i;
	char	*str;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] != '\n' && line[i])
		i++;
	str = (char *)malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (line[i] != '\n' && line[i])
	{
		str[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		str[i] = line[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_get_remainder(char *remainder)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free (remainder);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(remainder) - i + 1));
	if (!str)
		return (NULL);
	i++;
	while (remainder[i])
		str[j++] = remainder[i++];
	str[j] = '\0';
	free (remainder);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*remainder;
	int			num;

	num = 1;
	ft_check_for_errors(fd);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	ft_null_and_return(buf);
	while (num != 0 && !ft_strchr(remainder, '\n'))
	{
		num = read(fd, buf, BUFFER_SIZE);
		if (num < 0)
		{
			free (buf);
			return (NULL);
		}
		buf[num] = '\0';
		remainder = ft_strjoin_mod(remainder, buf);
	}
	free (buf);
	ft_null_and_return(remainder);
	line = ft_get_line(remainder);
	remainder = ft_get_remainder(remainder);
	return (line);
}
