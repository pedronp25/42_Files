/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:16:38 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/29 02:36:17 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	sl_check_arg(argc, argv[1]);
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

