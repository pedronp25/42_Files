/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 22:31:26 by pedromig          #+#    #+#             */
/*   Updated: 2025/07/03 00:29:32 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include <stdlib.h>
#include <unistd.h>

#define TILE_SIZE 96

typedef struct s_game {
	void	*mlx;
	void	*win;
	void	*img_floor;
	void	*img_wall;
}	t_game;

void	draw_scaled(t_game *game, void *img, int x, int y, int scale)
{
	for (int dy = 0; dy < scale; dy++)
	{
		for (int dx = 0; dx < scale; dx++)
		{
			mlx_put_image_to_window(game->mlx, game->win,
				img,
				(x * scale + dx) * TILE_SIZE,
				(y * scale + dy) * TILE_SIZE);
		}
	}
}

void	load_images(t_game *game)
{
	int	w;
	int	h;

	game->img_floor = mlx_xpm_file_to_image(game->mlx, "tile_img.xpm", &w, &h);
	game->img_wall = mlx_xpm_file_to_image(game->mlx, "cat_img.xpm", &w, &h);
	if (!game->img_floor || !game->img_wall)
	{
		write(2, "Error loading images\n", 22);
		exit(1);
	}
}

void	render(t_game *game)
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			mlx_put_image_to_window(game->mlx, game->win,
				game->img_floor, x * TILE_SIZE, y * TILE_SIZE);
		}
	}
	// Put cat only in center
	mlx_put_image_to_window(game->mlx, game->win,
		game->img_wall, 2 * TILE_SIZE, 2 * TILE_SIZE);
}

int	main(void)
{
	t_game	game;

	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);

	game.win = mlx_new_window(game.mlx, 5 * TILE_SIZE, 5 * TILE_SIZE, "so_long example");
	load_images(&game);
	render(&game);
	//draw_scaled(&game, game.img_floor, 1, 1, 4); // scale 2×

	mlx_loop(game.mlx);
	return (0);
}
