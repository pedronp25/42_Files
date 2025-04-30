/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:40:37 by pedromig          #+#    #+#             */
/*   Updated: 2025/04/26 21:59:34 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	int			bytes_read;
	char		*return_str;
	int			nl_check;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);

	bytes_read = 0;
	nl_check = 0;
	return_str = NULL;

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
			return(NULL);

		nl_check = ft_cleanup_str(buf);
	}
	return (return_str);
}

int	ft_strlen_nl(char *str)
{
	int	x;

	x = 0;
	if (!str)
		return (x);
	while (str[x] && str[x] != '\n')
		x++;
	if (str[x] == '\n')
		x++;
	return (x);
}

char	*ft_strjoin_nl(char *s1, char *s2)
{
	int		x;
	int		y;
	char	*final_str;

	x = 0;
	y = 0;
	final_str = malloc(ft_strlen_nl(s1) + ft_strlen_nl(s2) + 1);
	if (!final_str)
		return (free(s1), NULL);
	while (s1 && s1[x])
	{
		final_str[x] = s1[x];
		x++;
	}
	while (s2 && s2[y])
	{
		final_str[x] = s2[y];
		x++;
		if (s2[y] == '\n')
			break ;
		y++;
	}
	final_str[x] = '\0';
	return (free(s1), final_str);
}

int	ft_cleanup_str(char *str)
{
	int	check;
	int	x;
	int	y;

	x = 0;
	y = 0;
	check = 0;
	while (str[x])
	{
		if (check)
		{
			str[y] = str[x];
			y++;
		}
		if (str[x] == '\n')
			check = 1;
		str[x] = '\0';
		x++;
	}
	while (y < x)
	{
		str[y] = '\0';
		y++;
	}
	return (check);
}
