/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_flood_fill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 19:30:14 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/30 21:52:06 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_check_path(t_game *sl)
{
	char	**map_copy;
	t_found	found;

	map_copy = sl_dup_map(sl);
	found.collectible = 0;
	found.exit = 0;
	sl_flood_fill(map_copy, sl->player_x, sl->player_y, &found, sl);
	sl_free_map_copy(map_copy);
	if (found.collectible != sl->collectible_count || found.exit == 0)
		exit (1); // Error (no valid path for player)
}

char	**sl_dup_map(t_game *sl)
{
	char	**map_copy;
	int	y;

	map_copy = ft_calloc(sl->height + 1, sizeof(char *));

	y = 0;
	while (sl->map[y])
	{
		map_copy[y] = ft_strdup(sl->map[y]);
		if (!map_copy[y])
			exit (1); // Error (couldn't allocate memory)
		y++;
	}
	return (map_copy);
}

void	sl_flood_fill(char **map, int x, int y, t_found *found, t_game *sl)
{
	if (y < 0 || y >= sl->height || x < 0 || x >= sl->width)
		return ;
	if (map[y][x] == '1' || map[y][x] == 'X')
		return ;
	else if (map[y][x] == 'E')
		found->exit++;
	else if (map[y][x] == 'C')
		found->collectible++;

	map[y][x] = 'X'; // Mark as visited

	sl_flood_fill(map, x + 1, y, found, sl); // right
	sl_flood_fill(map, x - 1, y, found, sl); // left
	sl_flood_fill(map, x, y + 1, found, sl); // down
	sl_flood_fill(map, x, y - 1, found, sl); // up
}

void	sl_free_map_copy(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		free(map[y++]);
	free(map);
}
