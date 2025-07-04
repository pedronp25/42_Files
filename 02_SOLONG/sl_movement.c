/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_movement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:49:15 by pedromig          #+#    #+#             */
/*   Updated: 2025/07/04 18:18:55 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	sl_key_press(int keycode, t_game *sl)
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
	else if (keycode == ESC)
		sl_exit_success(sl, 1);
	else
		return (0);
	sl_move(new_y, new_x, sl);
	return (0);
}

void	sl_move(int y, int x, t_game *sl)
{
	char		pos;
	static int	was_on_exit = 0;

	pos = sl->map[y][x];
	if (pos == '1' || y < 0 || y >= sl->height || x < 0 || x >= sl->width)
		return ;
	if (pos == 'C')
		sl->collected++;
	if (pos == 'E')
	{
		if (sl->collected == sl->collectible_count)
			sl_exit_success(sl, 0);
		was_on_exit = 1;
	}
	if (was_on_exit && pos != 'E')
	{
		sl->map[sl->player_y][sl->player_x] = 'E';
		was_on_exit = 0;
	}
	else
		sl->map[sl->player_y][sl->player_x] = '0';
	sl_move_update(y, x, sl);
	sl_draw_map(sl);
}

void	sl_move_update(int y, int x, t_game *sl)
{
	sl->map[y][x] = 'P';
	sl->player_y = y;
	sl->player_x = x;
	sl->moves++;
	ft_printf("Number of moves: %i\n", sl->moves);
}
