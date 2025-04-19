/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:03:45 by pedromig          #+#    #+#             */
/*   Updated: 2025/04/19 17:09:29 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

 char	*get_next_line(int fd)
{
	int	i;
	size_t	bytes;
	char	*buf;

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
		if (buf[i] == '\n' || (!buf[i] && buf[i] != buf[bytes])) //Check if string has '\n' or if it has reached the end of the file (if it has reached a null and it hasn't filled the buffer)
	}
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*ptr2;

	if (!size)
	{
		free(ptr);
		return (NULL);
	}
	ptr2 = malloc(size);
	if (!ptr2)
		return (NULL);
	memmove(ptr2, ptr, size - BUFFER_SIZE); //'size - BUFFER_SIZE' to (hopefully) get the size of 'ptr'
	free (ptr);
	return (ptr2);
}
