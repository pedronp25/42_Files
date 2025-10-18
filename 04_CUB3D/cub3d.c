/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 23:21:21 by pedromig          #+#    #+#             */
/*   Updated: 2025/10/18 01:20:04 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	int		map_start_line;
	int		fd;

	cbd_check_arg(argc, argv, &fd);
	map_start_line = cbd_check_file(fd);
}

int	cbd_check_file(int fd)
{
	char	*line;
	int		line_count;
	int		tex_id[6];
	int		x;

	x = 0;
	while (x < 6)
		tex_id[x++] = 0;
	line_count = cbd_check_elements(&line, tex_id, fd);
	while (line != NULL && cbd_is_map(line))
	{
		line_count++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
	{
		free(line);
		cbd_error("Wrong file formatting");
	}
	close(fd);
	return (line_count);
}

int	cbd_check_elements(char **line, int *tex_id, int fd)
{
	int	line_count;

	*line = get_next_line(fd);
	if (!*line)
		cbd_error("Couldn't read the file");
	line_count = 0;
	while (*line != NULL)
	{
		ft_printf("%s", line); // DELETE LATER
		cbd_check_line(*line, tex_id);
		if (cbd_is_map(*line))
			break ;
		line_count++;
		free(*line);
		*line = get_next_line(fd);
	}
	return (line_count);
}

void	cbd_check_line(char *line, int *tex_id)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		cbd_mark_id(tex_id, NO);
	else if (ft_strncmp(line, "SO", 2) == 0)
		cbd_mark_id(tex_id, SO);
	else if (ft_strncmp(line, "WE", 2) == 0)
		cbd_mark_id(tex_id, WE);
	else if (ft_strncmp(line, "EA", 2) == 0)
		cbd_mark_id(tex_id, EA);
	else if (ft_strncmp(line, "F", 1) == 0)
		cbd_mark_id(tex_id, F);
	else if (ft_strncmp(line, "C", 1) == 0)
		cbd_mark_id(tex_id, C);
}

void	cbd_mark_id(int *tex_id, int id)
{
	if (tex_id[id] == 1)
		cbd_error("Duplicate texture or color identifier");
	else
		tex_id[id] = 1;
}

int	cbd_is_map(char *line)
{
	int	x;

	x = 0;
	while (line[x] && cbd_iswhitespace(line[x]))
		x++;
	if (line[x] == '1')
		return (1);
	return (0);
}

int	cbd_iswhitespace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	cbd_error(char *error_msg)
{
	//TO DO
	ft_printf("Error:\n%s!\n", error_msg);
	exit (1);
}
