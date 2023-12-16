/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffidha <ffidha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:27:21 by ffidha            #+#    #+#             */
/*   Updated: 2023/12/16 10:30:24 by ffidha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*readall(int fd, char *all)
{
	char	*nstr;
	int		bytes_read;

	nstr = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!nstr)
		return (NULL);
	bytes_read = 0;
	while (ft_strchr(all, '\n') == 0 && bytes_read != 0)
	{
		bytes_read = read(fd, nstr, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(nstr);
			return (NULL);
		}
		nstr[bytes_read] = '\0';
		all = ft_strjoin(all, nstr);
	}
	free(nstr);
	return (all);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*leftover;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (0);
	leftover = readall(fd, leftover);
	if (!leftover)
		return (NULL);
	line = gettheline(leftover);
	leftover = remain(leftover);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*next_line;
// 	int		count;

// 	count = 0;
// 	fd = open("example.txt", O_RDONLY);
// 	while (1)
// 	{
// 		next_line = get_next_line(fd);
// 		if (next_line == NULL)
// 			break ;
// 		count++;
// 		printf("[%d]:%s\n", count, next_line);
// 		next_line = NULL;
// 	}
// 	close(fd);
// 	return (0);
// }
