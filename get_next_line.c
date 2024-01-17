/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:32:27 by tbabou            #+#    #+#             */
/*   Updated: 2024/01/17 19:57:22 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	i;

	srcsize = ft_strlen(src);
	i = 0;
	if (dstsize > 0)
	{
		while (i < srcsize && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srcsize);
}

int	isnewline(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	get_final_size(char *s1, char *s2, char *buffer)
{
	int	size;

	size = 0;
	if (s1)
	{
		size = s1 - s2;
		ft_strlcpy(buffer, s1, BUFFER_SIZE + 1);
	}
	else
	{
		size = ft_strlen(s2);
		ft_strlcpy(buffer, "", BUFFER_SIZE + 1);
	}
	return (size);
}

char	*get_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*new_line;
	int			amount;
	int			final_size;

	amount = BUFFER_SIZE;
	line = ft_strdup(buffer);
	while (!isnewline(buffer) && (amount == BUFFER_SIZE || amount > 0))
	{
		amount = read(fd, buffer, BUFFER_SIZE);
		buffer[amount] = '\0';
		line = ft_strjoin(line, buffer);
	}
	if (!ft_strlen(line))
		return (free(line), NULL);
	new_line = ft_strrchr(line, '\n');
	final_size = get_final_size(new_line, line, buffer);
	line[final_size] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = get_line(fd);
	if (!line || line[0] == '\0')
		return (NULL);
	return (line);
}
