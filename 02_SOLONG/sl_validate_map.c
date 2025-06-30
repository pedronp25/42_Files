/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_validate_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:36:11 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/30 03:08:45 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_validate_map(t_game *sl)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (sl->map_file[y])
	{
		if (ft_strlen(sl->map_file[y]) != sl->width)
			exit (1); // Error (line in map doesn't have equal width)
		if (sl_check_chars(sl, y, x) == 1)
			exit (1); // Error (did not find one of the characters)
	}
}

int	sl_check_chars(t_game *sl, int y, int x)
{
	int	found_p;
	int	found_c;
	int	found_e;
	char tile;

	found_p = 0;
	found_c = 0;
	found_e = 0;
	while (sl->map_file[y][x])
	{
		tile = sl->map_file[y][x];
		if (tile == 'P')
		{
			found_p++;
			sl->player_y = y;
			sl->player_x = x;
		}
		else if (tile == 'C')
			found_c++;
		else if (tile == 'E')
			found_e++;
		else if (tile != '0' || tile != '1')
			return (1);
		if (y == 0 || y == sl->height - 1 || x == 0 || x == sl->width - 1)
			if (tile != '1')
				return (1);
	}
	if (!found_p || !found_c || !found_e)
		return (1);
	return (0);
}
