/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffidha <ffidha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:27:21 by ffidha            #+#    #+#             */
/*   Updated: 2024/01/16 14:59:40 by ffidha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
This function reads data from a file descriptor (fd) into a buffer until it encounters a newline character (\n).
It keeps appending the content to a variable called remaining, which holds the accumulated data read so far.
It returns NULL if there's an error or the end of the file is reached.
*/
char	*file_line_appender(int fd, char *remaining)
{
	int			read_bytes;
	char			*buffer;
	char			*temp;	

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
		temp = remaining; // avoid unnecessary copying and memory leaks by store a temporary copy of the remaining string before overwriting it in line_assigner (in get_next_line function).
		remaining = ft_strjoin(remaining, buffer); 
		free(temp);
	}
	return (free(buffer), remaining);
}
/*
This function takes the remaining string and finds the first occurrence of a newline character.
It extracts the portion of the string up to the newline (excluding the newline itself) and allocates memory for a new string to hold this extracted content.
It returns the newly created string containing the extracted line.
*/
char	*line_assigner(char *remaining)
{
	int		i;
	char		*extracted_line;

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
/*
This function takes the remaining string after extracting a line.
It finds the position of the first newline character (if any) remaining in the string.
It allocates memory for a new string and copies the remaining content after the newline (excluding the newline) to this new string.
It frees the original remaining string and returns the cleaned string.
*/
char	*buffer_cleaner(char *remaining)
{
	int			newline_i;
	int			cleanup_j;
	char			*cleaned;

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
/*
This function is the main function you call to get the next line from a file.
It first checks for invalid file descriptor, buffer size, etc.
It calls file_line_appender to ensure there's data in the remaining variable.
It calls line_assigner to extract the next line from the remaining string.
It calls buffer_cleaner to update the remaining string for the next iteration.
It frees the original remaining memory (no longer needed) and returns the extracted line.
*/
char	*get_next_line(int fd)
{
	static char	*remaining;
	char		*returnline;

	if (fd < 0 || BUFFER_SIZE < 1 || BUFFER_SIZE > INT_MAX)
		return (0);
	remaining = file_line_appender(fd, remaining);
	if (!remaining)
		return (NULL);
	returnline = line_assigner(remaining);
	remaining = buffer_cleaner(remaining);
	free(remaining);
	return (returnline);
}

// int main()
// {
// 	int fd;
// 	char *line;

// 	fd = open("ex.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("[1]: %s", line);
// 	free(line);
// 	line = get_next_line(fd);
// 	printf("[2]: %s", line);
// 	free(line);
// 	close (fd);
// }
