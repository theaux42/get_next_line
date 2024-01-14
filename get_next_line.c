/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:32:27 by tbabou            #+#    #+#             */
/*   Updated: 2024/01/14 20:18:36 by tbabou           ###   ########.fr       */
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
	returned = (char *)malloc(len + 1);
	if (!returned)
		return (NULL);
	while (i < len)
	{
		returned[i] = str[i];
		i++;
	}
	returned[i + 1] = '\n';
	return (returned);
}

char	*get_line(int fd)
{
	static char	*stash;
	char		*line;
	char		buffer[BUFFER_SIZE];
	int			amount;

	amount = 0;
	line = ft_strdup("");
	if (!stash)
		stash = ft_strdup("");
	while (!isnewline(stash))
	{
		ft_memset(buffer, '\0', BUFFER_SIZE);
		amount = read(fd, buffer, BUFFER_SIZE);
		stash = ft_strjoin(stash, buffer);
		if (amount != BUFFER_SIZE)
			break ;
	}
	line = ft_cleanup(ft_strdup(stash));
	stash = ft_strrchr(stash, '\n');
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	line = get_line(fd);
	if (!line || line[0] == '\0')
		return (NULL);
	return (line);
}
