/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_initialization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 21:57:48 by pedromig          #+#    #+#             */
/*   Updated: 2025/07/03 20:07:34 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "so_long.h"

void	sl_check_arg(int argc, char *file)
{
	char	*extension;

	if (argc != 2)
	{
		ft_printf("Usage: ./so_long '.ber file'\n");
		exit (1);
	}
	extension = ft_strrchr(file, '.');
	if (!extension || ft_strncmp(extension, ".ber", 4) != 0)
	{
		ft_printf("%s isn't a valid file!\n\tValid map file: '*.ber'\n", file);
		exit (1);
	}
}

int	sl_count_lines(char *file)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(1); // Error opening file
	line = get_next_line(fd);
	height = 0;
	while (line != NULL)
	{
		free(line);
		height++;
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

t_game	*sl_init(char *file, int height)
{
	t_game	*sl;

	sl = ft_calloc(1, sizeof(t_game));
	if (!sl)
		exit (1); // Error (couldn't allocate memory)
	sl->height = height;
	sl->map = ft_calloc(height + 1, sizeof(char *));
	if (!sl->map)
		exit (1); // Error (couldn't allocate memory)
	return (sl);
}

void	sl_store_map(char *map_file, t_game *sl)
{
	int	fd;
	int	y;
	int	x;
	
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		exit (1); // Error opening file
	y = 0;
	while (y < sl->height)
	{
		sl->map[y] = get_next_line(fd);
		if (!sl->map[y])
			exit (1); // Error (unexpected end of file)
		sl->map[y][ft_strlen(sl->map[y])] = '\0';
		y++;
	}
	sl->width = ft_strlen(sl->map[0]) - 1;
	y = 0;
	while (y < sl->height) // Print map to verify it's correct
		ft_printf("%s", sl->map[y++]);
}
