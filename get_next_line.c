/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbabou <tbabou@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 22:32:27 by tbabou            #+#    #+#             */
/*   Updated: 2024/01/13 00:15:36 by tbabou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*

SCHEMA :
 => Lecture de n char
 => Stockage de n char dans stash
 => verification de la présence de /n dans stash
 => si il y a /n alors
	=> copie de stash dans line jusqu'a /n
	=> suppression de line dans la stash
	=> return de line
 => sinon
	continuer la loop

*/


char	*get_line(int fd)
{
	static char	*stash;
	char		*line;
	char		buffer[BUFFER_SIZE + 1];
	int			amount;

	amount = 0;
	if (!stash)
		stash = ft_strdup("");
	while (!isnewline(stash))
	{
		amount = read(fd, buffer, BUFFER_SIZE); // Lecture du texte
		stash = ft_strjoin(line, buffer);
		ft_memset(buffer, '\0', BUFFER_SIZE + 1);
		if (amount != BUFFER_SIZE)
			break ;
	}
	line = ft_strdup(stash);
	line = ft_cleanup(line);
	stash = ft_strrchr(stash, '\n');
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (BUFFER_SIZE < 0 || fd < 0)
		return (NULL);
	line = get_line(fd);
	if (!line)
		return (NULL);
	return (line);
}

void printfresult(char *str)
{
	if (!str)
		printf("NULL returned \n");
	else
		printf("=> %s\n", str);	
}

int	main(void)
{
	int fd;
	char *line;

	fd = open("text.txt", O_RDONLY);
	line = get_next_line(fd);
	printf("==== RESULT ====\n");
	printfresult(line);
	line = get_next_line(fd);
	printf("==== RESULT ====\n");
	printfresult(line);
	line = get_next_line(fd);
	printf("==== RESULT ====\n");
	printfresult(line);
	line = get_next_line(fd);
	printf("==== RESULT ====\n");
	printfresult(line);
}
