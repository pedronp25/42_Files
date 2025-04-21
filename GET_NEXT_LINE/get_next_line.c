/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:03:45 by pedromig          #+#    #+#             */
/*   Updated: 2025/04/21 21:18:20 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int		i;
	int		bytes;
	char	*buf;
	char	*ret_str;
	static char	*saved_str = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	ret_str = NULL;
	if (saved_str)
	{
		ret_str = ft_strdup(saved_str);
		free(saved_str);
		saved_str = NULL;
	}
	bytes = read(fd, buf, BUFFER_SIZE);
	while (bytes > 0)
	{
		i = 0;
		buf[bytes] = '\0';
		ret_str = ft_strjoin_free(ret_str, buf);
		while (ret_str[i] && ret_str[i] != '\n')
			i++;
		if (ret_str[i] == '\n')
		{
			saved_str = ft_strdup(&ret_str[i + 1]);
			ret_str[i + 1] = '\0';
			break ;
		}
		bytes = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (!ret_str || ret_str[0] == '\0')
	{
		free(ret_str);
		return (NULL);
	}
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
