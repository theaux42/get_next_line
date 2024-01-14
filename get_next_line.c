/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:32:27 by tbabou            #+#    #+#             */
/*   Updated: 2024/01/14 20:14:28 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
