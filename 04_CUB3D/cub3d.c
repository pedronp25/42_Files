/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 23:21:21 by pedromig          #+#    #+#             */
/*   Updated: 2025/10/17 01:12:54 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	//t_map	*map;
	int		fd;

	cbd_valid_arg(argc, argv, &fd);
	cbd_valid_textures(fd);
}

void	cbd_valid_file(int fd)
{
	char	*line;
	int		x;

	x = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_printf("%s", line);
		x++;
		line = get_next_line(fd);
	}
	close(fd);

}

void	cbd_valid_textures(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	// Need to figure out basic structs before
	// So that I can check for the textures in the file
		// and instantly keep it in a struct

}

void	cbd_error(char *error_msg)
{
	//TO DO
	ft_printf("Error\n%s\n", error_msg);
	exit (1);
}
