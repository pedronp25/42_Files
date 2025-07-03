/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_validate_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 02:36:11 by pedromig          #+#    #+#             */
/*   Updated: 2025/07/03 03:46:01 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_validate_map(t_game *sl)
{
	t_found	found;
	int	y;
	int	x;

	found.player = 0;
	found.exit = 0;
	found.collectible = 0;
	y = 0;
	x = 0;
	if (sl->width < 3 || sl->height < 3)
		exit (1); // Error (map must be at least 3x3)
	while (sl->map[y])
	{
		x = 0;
		sl_check_chars(sl, &found, y, x);
		x = 0;
		sl_check_walls(sl, y, x);
		y++;
	}
	if (found.player != 1 || found.exit != 1 || found.collectible == 0)
		exit (1); // Error (number of 'P', 'E' or 'C' isn't valid)
	sl->collectible_count = found.collectible;
}

void	sl_check_chars(t_game *sl, t_found *found, int y, int x)
{
	char	tile;

	while (sl->map[y][x] && sl->map[y][x] != '\n')
	{
		tile = sl->map[y][x];
		if (tile == 'P')
		{
			found->player++;
			sl->player_y = y;
			sl->player_x = x;
		}
		else if (tile == 'E')
			found->exit++;
		else if (tile == 'C')
			found->collectible++;
		else if (tile != '0' && tile != '1')
			exit (1);
		x++;
	}
}

void	sl_check_walls(t_game *sl, int y, int x)
{
	if (ft_strlen(sl->map[y]) != sl->width)
		exit (1); // Error (line in map doesn't have equal width)
	while (sl->map[y][x] && sl->map[y][x] != '\n')
	{
		if (y == 0 || y == sl->height - 1 || x == 0 || x == sl->width - 1)
			if (sl->map[y][x] != '1')
				exit (1); // Error (Hole in the wall)
		x++;
	}
}
