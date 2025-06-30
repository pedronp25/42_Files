/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:16:38 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/30 03:10:39 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game	*sl;

	sl_check_arg(argc, argv[1]);
	sl_store_map(argv[1], sl);
	sl_validate_map(sl);
}

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

void	sl_store_map(char *map_file, t_game *sl)
{
	int	fd;
	int	y;
	int	x;

	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		exit (1); // Error opening file
	sl->map_file[0] = get_next_line(fd);
	y = 1;
	while (sl->map_file[y] != NULL) // Read file, store it and count height
		sl->map_file[y++] = get_next_line(fd);
	while (sl->map_file[0][x]) // Count width
		x++;
	sl->height = y;
	sl->width = x;
	while (y > 0) // Print map to verify it's correct
		ft_printf("%s", sl->map_file[sl->height - y--]);
}

