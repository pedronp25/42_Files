/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:39:07 by pedromig          #+#    #+#             */
/*   Updated: 2025/04/20 00:30:58 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	ft_strlcat(final_str, s1, s1_len); //originally using ft_strlcpy
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

char	*ft_strdup(const char *s)
{
	char	*copy;
	size_t	size;

	size = ft_strlen(s) + 1;
	copy = malloc(size);
	if (!copy)
		return (NULL);
	ft_strlcat(copy, s, size);
	return (copy);
}

int	initial_checks(int fd, char *ret_str, char *buf, int bytes)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
		return (0);
	ret_str = NULL;
//	if (!ret_str || *ret_str == '\0')
//		saved_str = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	bytes = read(fd, buf, BUFFER_SIZE);
	if (bytes == -1)
		return (0);
	return (1);
}
