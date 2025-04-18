#include "get_next_line.h"

 char	*get_next_line(int fd)
{
	int	i;
	size_t	bytes;
	char	buf[BUF_SIZE];

	bytes = read(fd, buf, BUF_SIZE - 1);
	i = 0;
	while (bytes != '\n')
	{
		buf[bytes] = '\0';
		
	}
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*ptr2;

	ptr2 = malloc(sizeof(ptr))
}

