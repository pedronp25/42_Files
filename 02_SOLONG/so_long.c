/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 20:16:38 by pedromig          #+#    #+#             */
/*   Updated: 2025/07/01 01:01:02 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game	*sl;
	int	height;

	sl_check_arg(argc, argv[1]);
	height = sl_count_lines(argv[1]);
	sl = sl_init(argv[1], height);
	sl_store_map(argv[1], sl);
	sl_validate_map(sl);
	sl_check_path(sl);
}

