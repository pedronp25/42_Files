/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:03:45 by pedromig          #+#    #+#             */
/*   Updated: 2025/04/19 16:07:22 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

 char	*get_next_line(int fd)
{
	int	i;
	size_t	bytes;
	char	buf[BUFFER_SIZE];

	buf = malloc(BUFFER_SIZE);
	if (!buf)
		return (NULL);
	bytes = read(fd, buf, BUFFER_SIZE - 1);
	if (bytes == -1)
		return (NULL);
	i = 0;
	while (buf[i] != '\n' && buf[i])
	{
		buf[bytes] = '\0';
		
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


