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

char	*file_line_appender(int fd, char *remaining) //magnifying glass
{
	int		read_bytes;
	char		*buffer;
	char		*temp;	

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && !ft_strchr(remaining, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes <= 0)
		{
			free(buffer);
			if (read_bytes == 0)
				return (remaining);
			free(remaining);
			return (0);
		}
		buffer[read_bytes] = '\0';
		temp = remaining;
		remaining = ft_strjoin(remaining, buffer);
		free(temp);
	}
	return (free(buffer), remaining);
}

char	*line_assigner(char *remaining) //scissors
{
	int		i;
	char	*extracted_line;

	i = 0;
	while (remaining[i] && remaining[i] != '\n')
		i++;
	if (remaining[i] == '\n')
		i++;
	extracted_line = (char *)malloc(sizeof(char) * (i + 1));
	if (!extracted_line)
		return (NULL);
	i = 0;
	while (remaining[i] != '\n' && remaining[i])
	{
		extracted_line[i] = remaining[i];
		i++;
	}
	if (remaining[i] == '\n')
	{
		extracted_line[i] = remaining[i];
		i++;
	}
	extracted_line[i] = '\0';
	return (extracted_line);
}

char	*buffer_cleaner(char *remaining) //remaining --> temp storage for the words
{
	int		newline_i;
	int		cleanup_j;
	char		*cleaned;

	newline_i = 0;
	while (remaining[newline_i] && remaining[newline_i] != '\n')
		newline_i++;
	if (remaining[newline_i] == '\n')
		newline_i++;
	if (!remaining[newline_i] || !remaining)
	{
		free(remaining);
		return (NULL);
	}
	cleaned = malloc(ft_strlen(remaining) - newline_i + 1);
	if (!cleaned)
	{
		free(remaining);
		return (NULL);
	}
	cleanup_j = 0;
	while (remaining[newline_i])
		cleaned[cleanup_j++] = remaining[newline_i++];
	cleaned[cleanup_j] = '\0';
	return (free(remaining), cleaned);
}

char	*get_next_line(int fd) //brain of the process, cordinates everything
{
	static char	*remaining; //string serves as a temporary storage space for text between function calls.
	char		*returnline;

	if (fd < 0 || BUFFER_SIZE < 1 || BUFFER_SIZE > INT_MAX)
		return (0);
	remaining = file_line_appender(fd, remaining);
	if (!remaining)
		return (NULL);
	returnline = line_assigner(remaining);
	remaining = buffer_cleaner(remaining);
	return (returnline);
}
