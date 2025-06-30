/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 03:26:05 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/30 03:10:07 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include <fcntl.h>

typedef struct	s_game
{
	char	**map_file;
	int	width;
	int	height;
	int	player_x;
	int	player_y;
}	t_game;

void	sl_check_arg(int argc, char *file);
void	sl_store_map(char *map_file, t_game *sl);
void	sl_validate_map(t_game *sl);
int		sl_check_chars(t_game *sl, int y, int x);

#endif
