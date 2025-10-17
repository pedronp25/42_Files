/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 23:21:21 by pedromig          #+#    #+#             */
/*   Updated: 2025/10/17 22:01:47 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	//t_map	*map;
	int		fd;

	cbd_check_arg(argc, argv, &fd);
	cbd_check_file(fd);
}

void	cbd_check_file(int fd)
{
	char	*line;
	int		tex_id[6];
	int		map_found;
	int		x;

	x = 0;
	while (x < 6)
		tex_id[x++] = 0;
	x = 0;
	line = get_next_line(fd);
	map_found = 0;
	while (line != NULL)
	{
		ft_printf("%s", line); // DELETE LATER
		cbd_check_tex_id(line, tex_id);
		if (cbd_map_found(line))
		{
			map_found = 1;
			break ;
		}
		x++;
		line = get_next_line(fd);
	}
	while (line != NULL && map_found)
	{
		
	}
	close(fd);
}

int	cbd_map_found(char *line)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (cbd_iswhitespace(line[x]))
			x++;
		if (line[x] == 1)
			return (1);
	}
	return (0);
}

int	cbd_iswhitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	cbd_check_tex_id(char *line, int *tex_id)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		cbd_check_dup_id(tex_id, NO);
	else if (ft_strncmp(line, "SO", 2) == 0)
		cbd_check_dup_id(tex_id, SO);
	else if (ft_strncmp(line, "WE", 2) == 0)
		cbd_check_dup_id(tex_id, WE);
	else if (ft_strncmp(line, "EA", 2) == 0)
		cbd_check_dup_id(tex_id, EA);
	else if (ft_strncmp(line, "F", 1) == 0)
		cbd_check_dup_id(tex_id, F);
	else if (ft_strncmp(line, "C", 1) == 0)
		cbd_check_dup_id(tex_id, C);
}

void	cbd_check_dup_id(int *tex_id, int id)
{
	if (tex_id[id] == 1)
		cbd_error("Duplicate texture or color identifier");
	else
		tex_id[id] = 1;
}

void	cbd_error(char *error_msg)
{
	//TO DO
	ft_printf("Error:\n%s!\n", error_msg);
	exit (1);
}
