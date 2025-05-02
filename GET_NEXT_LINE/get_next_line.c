/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:40:37 by pedromig          #+#    #+#             */
/*   Updated: 2025/04/30 17:50:04 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
<<<<<<< HEAD
	int		bytes;
	char	*buf;
	char	*ret_str;
	static char	*saved_str = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (NULL); // Check invalid parameters

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // Calloc for null-terminating
	if (!buf)
		return (NULL);

	ret_str = NULL; // Initialize return string
	bytes = read(fd, buf, BUFFER_SIZE); // Read into buffer

	while (bytes > 0) // Continue until 'read' reaches EOF or an error occurs
	{
		while (*buf != '\n' && *buf != '\0') // Iterate through buffer
			buf++;

		// If a newline is found, save the rest of the string for the next call
		if (*buf == '\n')
		{
			saved_str = ft_strdup(buf + 1); // Skip the newline character
			*buf = '\0'; // Null-terminate at the newline
		}

		// Join current part to the return string
		ret_str = ft_strjoin_free(ret_str, buf);

		// Read the next chunk of data
		bytes = read(fd, buf, BUFFER_SIZE);
	}

	// If nothing has been added to ret_str and saved_str is not NULL, return saved_str
	if (ret_str == NULL && saved_str != NULL)
	{
		ret_str = ft_strdup(saved_str);
		free(saved_str);
		saved_str = NULL;
	}

	free(buf);
	return (ret_str);
}

static void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;
	size_t	total_size;
	size_t	x;
	char	*temp;

	total_size = n * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	x = 0;
	temp = ptr;
	while (x < n)
	{
		temp[x] = '\0';
		x++;
	}
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	int	x;

	x = 0;
	if (!(char)c)
		return ((char *)&s[ft_strlen(s)]);
	while (s[x])
	{
		if (s[x] == (char)c)
			return ((char *)&s[x]);
		x++;
	}
	return (NULL);
}



char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
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
=======
	static char	buf[BUFFER_SIZE + 1];
	int			bytes_read;
	char		*return_str;
	int			nl_check;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	ft_ultimate_initializer(&bytes_read, &nl_check, &return_str);
	while (!nl_check)
	{
		if (!buf[0])
		{
			bytes_read = read(fd, buf, BUFFER_SIZE);
			if (bytes_read == -1)
				return (free(return_str), NULL);
			if (bytes_read == 0)
				break ;
			buf[bytes_read] = '\0';
		}
		return_str = ft_strjoin_nl(return_str, buf);
		if (!return_str)
			return (NULL);
		nl_check = ft_cleanup_str(buf);
	}
	return (return_str);
}
>>>>>>> 37589316ea04e310ed37395a1859ca9c3ab99e41
