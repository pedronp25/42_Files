/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:03:45 by pedromig          #+#    #+#             */
/*   Updated: 2025/04/19 22:56:21 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

 char	*get_next_line(int fd)
{
	int	i;
	int	bytes;
	char	*buf;
	char	*ret_str;
	static char	*saved_str;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	saved_str = NULL;
	ret_str = NULL;
	buf = malloc(BUFFER_SIZE);
	if (!buf)
		return (NULL);
	bytes = read(fd, buf, BUFFER_SIZE - 1);
	if (bytes == -1)
		return (NULL);
	i = 0;
	while (bytes)
	{
		buf[bytes] = '\0';
		while (buf[i] != '\n' && buf[i])
			i++;
		if (buf[i] == '\n' || (!buf[i] && i != bytes)) //Check if string has '\n' or if it has reached the end of the file (if it has reached a null and it hasn't filled the buffer)
		{
			free(saved_str);
			saved_str = ft_strdup(&buf[i]);
			break ;
		}
		else
		{
			ft_strjoin(ret_str, buf);
			bytes = read(fd, buf, BUFFER_SIZE - 1);
		}
	}
	free(buf);
	return (ret_str);
}

// Main to test
/*
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2) {
		// Check if the user provided a file name as argument
		printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}

	// Open the file in read-only mode
	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		// If file cannot be opened, print an error message
		perror("Error opening file");
		return (1);
	}

	// Call get_next_line() in a loop to read the file line by line
	while ((line = get_next_line(fd)) != NULL) {
		// Print each line returned by get_next_line
		printf("%s", line);
		free(line);  // Don't forget to free the memory after using it
	}

	// Close the file descriptor after reading is complete
	close(fd);

	return (0);
}
*/
