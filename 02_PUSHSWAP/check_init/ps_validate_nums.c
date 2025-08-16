/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_validate_nums.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:28:16 by pedromig          #+#    #+#             */
/*   Updated: 2025/07/29 19:48:16 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

char	**ps_args_check(int argc, char **argv)
{
	char	**matrix;
	int		x;

	if (argc == 1)
		exit (1);
	if (argc == 2)
	{
		matrix = ft_split(argv[1], ' ');
		if (!matrix)
			exit (1);
	}
	matrix = ft_calloc(argc - 1, sizeof(char));
	if (!matrix)
		exit (1);
	x = 1;
	while (x < argc)
	{
		matrix[x - 1] = argv[x];
		x++;
	}
	return (matrix);
}

int	*ps_validate_str_arr(char **str_arr, int *int_arr_len)
{
	int	x;
	int y;
	int	*int_arr;

	x = 0;
	int_arr = ft_calloc(ps_strarr_len(str_arr), sizeof(int));
	while (str_arr && str_arr[x])
	{
		y = 0;
		if (str_arr[x][y] == '-' || str_arr[x][y] == '+')
			y++;
		while (str_arr[x][y])
		{
			if (str_arr[x][y] < '0' || str_arr[x][y] > '9')
				exit (1); // Error: not a number
			y++;
		}
		int_arr[x] = ft_atoi(str_arr[x]);
		x++;
	}
	ps_check_duplicates(int_arr, x);
	*int_arr_len = x;
	return (int_arr);
}

int	ps_strarr_len(char **str_arr)
{
	int	x;

	x = 0;
	while (str_arr && str_arr[x])
		x++;
	return (x);
}

void	ps_check_duplicates(int	*arr, int len)
{
	int	x;
	int	y;

	x = 0;
	while (x < len)
	{
		y = x + 1;
		while (y < len)
			if (arr[x] == arr[y++])
				exit (1); // Error: found a duplicate
		x++;
	}
}
