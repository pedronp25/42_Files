/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 19:26:02 by pedromig          #+#    #+#             */
/*   Updated: 2025/04/14 21:10:10 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_words(char *str, char c);
void	free_arr(char *meow);

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		pos;
	int		x;
	int		y;

	arr = malloc((count_words((char *)s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	x = 0;
	y = 0;
	pos = 0;
	while (s[x])
	{
		while (s[y] == c)
			y++;
		if (s[y] == c || !s[y])
		{
			arr[pos] = ft_substr(s, x, (y - x));
			if (!arr[pos])
			{
				free_arr(*arr);
				return (NULL);
			}
			pos++;
			while (s[y] == c)
				y++;
			x = y;
		}
		y++;
	}
	return (arr);
}

int	count_words(char *str, char c)
{
	int	x;
	int	word_count;

	x = 0;
	word_count = 0;
	while (str[x])
	{
		if (str[x] != c)
		{
			word_count++;
			while (str[x] != c && str[x])
				x++;
		}
		else
			x++;
	}
	return (word_count);
}

void	free_arr(char **meow)
{
	int	x;

	x = 0;
	while (meow[x])
	{
		free((void *)&meow[x]);
		x++;
	}
	free(meow);
}
