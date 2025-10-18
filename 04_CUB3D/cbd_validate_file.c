/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cbd_validate_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 00:04:46 by pedromig          #+#    #+#             */
/*   Updated: 2025/10/18 00:34:53 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cbd_check_arg(int argc, char **argv, int *fd)
{
	char	*extension;

	if (argc != 2)
		cbd_error("Invalid number of arguments");
	extension = ft_strchr(argv[1], '.');
	if (!extension || ft_strncmp(extension, ".cub", 4) != 0)
		cbd_error("Invalid file extension");
	*fd = open(argv[1], O_RDONLY);
	if (*fd == -1)
		cbd_error("Couldn't open .cub file");
}

