/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 23:28:20 by pedromig          #+#    #+#             */
/*   Updated: 2025/10/17 22:01:49 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define C 4
# define F 5

# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "mlx/mlx.h"

typedef struct s_mapinfo
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	*floor_color;
	char	*ceilling_color;
}	t_mapinfo;

typedef struct s_data
{
	char		**map;
	t_mapinfo	*mapinfo;

}	t_data;

void	cbd_check_arg(int argc, char **argv, int *fd);
void	cbd_check_file(int fd);
void	cbd_check_tex_id(char *line, int *tex_id);
void	cbd_check_dup_id(int *tex_id, int id);

void	cbd_error(char *error_msg);

#endif
