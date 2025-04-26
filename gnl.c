
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

#include <unistd.h>

char	*get_next_line(int fd);
static char *read_file(int fd);
static void	*ft_calloc(size_t n, size_t size)

include "get_next_line"

char	*get_next_line(int fd)
{
	char	*buf;

	buf = read_file(fd);
	return (buf);
}

static char	*read_file(int fd) // To read from the file
{
	int	bytes_read;
	char	*buf;

	buf = ft_calloc (BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	bytes_read = read (fd, buf, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (free(buf), NULL);
	return (buf);

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

#include <stdio.h>
#include <fcntl.h>
int	main(int argc, char *argv[])
{
	if (argc != 2)
			return (1);

	char	*file = argv[1];
	int	fd = open (file, O_RDONLY);
	char	*next_line;
	if (fd < 0)
		return (2);
	while (1)
	{
		next_line = get_next_line(fd);
		if (!next_line)
			break ;
		printf("%s", next_line);
		free (next_line);
		next_line = NULL;
	}
	close(fd);
	return (0);
}
