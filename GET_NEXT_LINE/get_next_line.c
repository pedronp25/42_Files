/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:03:45 by pedromig          #+#    #+#             */
/*   Updated: 2025/04/19 17:53:46 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

 char	*get_next_line(int fd)
{
	int	i;
	size_t	bytes;
	char	*buf;
	char	*ret_str;

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
			break ;
		else
		{
			ft_strjoin(ret_str, buf);
			bytes = read(fd, buf, BUFFER_SIZE - 1);
		}
	}
	return (ret_str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*final_str;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_size;

	s1_len = ft_strlen(s1) + 1;
	s2_len = ft_strlen(s2) + 1;
	total_size = s1_len + s2_len;
	final_str = malloc(total_size - 1);
	if (!final_str)
		return (NULL);
	ft_strlcpy(final_str, s1, s1_len);
	ft_strlcat(final_str, s2, total_size);
	return (final_str);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	x;
	size_t	y;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	x = dest_len;
	y = 0;
	if (size == 0)
		return (src_len);
	while (src[y] && x < (size - 1))
	{
		dst[x] = src[y];
		x++;
		y++;
	}
	dst[x] = '\0';
	if (size <= dest_len)
		return (src_len + size);
	else
		return (src_len + dest_len);
}

size_t	ft_strlen(const char *s)
{
	size_t	x;

	x = 0;
	while (s[x])
		x++;
	return (x);
}

void	*ft_realloc(void *ptr, size_t size) //Don't know if I'm going to use this
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
