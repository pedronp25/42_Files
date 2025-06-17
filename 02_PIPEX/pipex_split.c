/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:21:55 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/17 18:25:03 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#include "libft.h"

static int	count_words(char *str, char c);
static void	initializer(int *i, int *j, int *pos);
static void	free_arr(char **str);

char	**pipex_split(char const *s, char c)
{
	char	**arr;
	int		pos;
	int		x;
	int		y;

	arr = ft_calloc(count_words((char *)s, c) + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	ultimate_ft_initializer(&x, &y, &pos);
	while (s[x])
	{
		while (s[y] && s[y] == c)
			y++;
		x = y;
		while (s[y] != c && s[y])
			y++;
		if (y > x)
		{
			arr[pos] = ft_substr(s, x, (y - x));
			if (!arr[pos])
				return (free_arr(arr), NULL);
			pos++;
		}
	}
	return (arr);
}

static int	count_words(char *str, char c)
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

static void	initializer(int *i, int *j, int *pos)
{
	*i = 0;
	*j = 0;
	*pos = 0;
}

static void	free_arr(char **str)
{
	int	x;

	x = 0;
	while (str[x++])
		free(str[x]);
	free(str);
}
