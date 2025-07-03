/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 02:11:07 by pedromig          #+#    #+#             */
/*   Updated: 2025/07/03 03:16:36 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "so_long.h"

void	sl_window(t_game *sl)
{
	int	size;

	sl->mlx = mlx_init();
	if (!sl->mlx)
		exit (1);
	sl->win = mlx_new_window(sl->mlx, sl->width * TILE_SIZE, sl->height * TILE_SIZE, "SO_LONG");
	sl->img.floor = mlx_xpm_file_to_image(sl->mlx, "96x96_imgs/floor_img.xpm", &size, &size);
	sl->img.wall = mlx_xpm_file_to_image(sl->mlx, "96x96_imgs/wall_img.xpm", &size, &size);
	sl->img.player = mlx_xpm_file_to_image(sl->mlx, "96x96_imgs/cat_img.xpm", &size, &size);
	sl->img.collectible = mlx_xpm_file_to_image(sl->mlx, "96x96_imgs/cat_img.xpm", &size, &size);
	sl->img.exit = mlx_xpm_file_to_image(sl->mlx, "96x96_imgs/cat_img.xpm", &size, &size);
	mlx_key_hook(sl->win, sl_key_press, sl);
	mlx_loop(sl->mlx);
}

void	sl_draw_map(t_game *sl)
{
	int	y;
	int	x;

	y = 0;
	while (y < sl->height)
	{
		x = 0;
		while (x < sl->width)
		{
			sl_draw_tile(sl, y, x);
			x++;
		}
		y++;
	}
}

void	sl_draw_tile(t_game *sl, int y, int x)
{
	char	tile;
	void	*img;

	img = NULL;
	tile = sl->map[y][x];
	mlx_put_image_to_window(sl->mlx, sl->win, sl->img.floor, x * TILE_SIZE, y * TILE_SIZE);

	if (tile == '1')
		img = sl->img.wall;
	else if (tile == 'P')
		img = sl->img.player;
	else if (tile == 'C')
		img = sl->img.collectible;
	else if (tile == 'E')
		img = sl->img.exit;

	if (img)
		mlx_put_image_to_window(sl->mlx, sl->win, img, x * TILE_SIZE, y * TILE_SIZE);
}
