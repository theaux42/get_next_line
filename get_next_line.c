/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:32:27 by tbabou            #+#    #+#             */
/*   Updated: 2024/01/15 01:58:36 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_cleanup(char *str)
{
	char	*returned;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (str[len] && str[len] != '\n')
		len++;
	len++;
	returned = (char *)malloc(len);
	if (!returned)
		return (NULL);
	while (i < len)
	{
		returned[i] = str[i];
		i++;
	}
	return (returned);
}

char	*get_line(int fd)
{
	static char	*stash;
	char		*line;
	char		buffer[BUFFER_SIZE];
	int			amount;

	amount = 0;
	if (!stash)
		stash = ft_strdup("");
	line = ft_strdup("");
	while (!isnewline(stash))
	{
		ft_memset(buffer, '\0', BUFFER_SIZE);
		amount = read(fd, buffer, BUFFER_SIZE);
		stash = ft_strjoin(stash, buffer);
		if (amount != BUFFER_SIZE)
			break ;
	}
	free(line);
	line = ft_strdup("");
	line = ft_cleanup(ft_strdup(stash));
	stash = ft_strrchr(stash, '\n');
	// if (line[0] != '\0' && amount == BUFFER_SIZE)
	// 	line[ft_strlen(line)] = '\n';
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	line = get_line(fd);
	if (!line || line[0] == '\0')
		return (NULL);
	return (line);
}

int	main(void)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open("text.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("[%i] => %s", i, line);
		line = get_next_line(fd);
		i++;
	}
}
