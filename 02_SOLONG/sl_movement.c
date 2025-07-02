/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:49:15 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/30 23:49:55 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_key_press(int keycode, t_game *sl)
{
	int	new_y;
	int	new_x;

	new_y = sl->player_y;
	new_x = sl->player_x;
	if (keycode == KEY_W)
		new_y--;
	else if (keycode == KEY_A)
		new_x--;
	else if (keycode == KEY_S)
		new_y++;
	else if (keycode == KEY_D)
		new_x++;
	sl_move(new_y, new_x, sl);
	if (keycode == ESC)
		exit (0); // Unsure if should use mlx_destroy_window in here
}

void	sl_move(int y, int x, t_game *sl)
{
	char	pos;

	if (pos == '1' || y < 0 || y >= sl->height || x < 0 || x >= sl->width)
		return ;
	pos = sl->map[y][x];
	if (pos == 'C')
		sl->collected++;
	if (pos == 'E')
	{
		if (sl->collected < sl->collectible_count)
			return ;
		mlx_destroy_window(sl->mlx, sl->win);
		exit(0); // All collectibles collected, player exits
	}
	sl->map[sl->player_y][sl->player_x] = '0'; // Old position
	sl->map[y][x] = 'P'; // New position
	sl->player_y = y;
	sl->player_x = x;
	sl->moves++;
	ft_printf("Number of moves: %i\n", sl->moves);
	//sl_redraw_map(); // Function to redraw the map after moving
}
