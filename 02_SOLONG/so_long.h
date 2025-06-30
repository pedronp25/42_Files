/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 03:26:05 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/30 21:49:37 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include <fcntl.h>

typedef struct	s_game
{
	char	**map;
	int	width;
	int	height;
	int	player_x;
	int	player_y;
	int	collectible_count;
}	t_game;

typedef struct	s_found
{
	int	player;
	int	exit;
	int	collectible;
}	t_found;

void	sl_check_arg(int argc, char *file);
t_game	*sl_init(char *file, int height);
int		sl_count_lines(char *file);
void	sl_store_map(char *map_file, t_game *sl);
void	sl_validate_map(t_game *sl);
void	sl_check_chars(t_game *sl,t_found *found, int y, int x);
void	sl_check_walls(t_game *sl, int y, int x);
void	sl_check_path(t_game *sl);
char	**sl_dup_map(t_game *sl);
void	sl_flood_fill(char **map, int x, int y, t_found *found, t_game *sl);
void	sl_free_map_copy(char **map);

#endif
