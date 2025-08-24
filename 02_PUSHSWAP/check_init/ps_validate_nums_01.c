/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_validate_nums_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 15:28:16 by pedromig          #+#    #+#             */
/*   Updated: 2025/08/25 00:54:15 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

char	**ps_args_check(t_stack *stack, int argc, char **argv)
{
	char	**matrix;

	if (argc == 1)
		ps_error(stack);
	else if (argc == 2)
	{
		matrix = ft_split(argv[1], ' ');
		if (!matrix || !matrix[0])
			ps_error(stack);
		return (matrix);
	}
	matrix = ft_calloc(argc, sizeof(char *));
	if (!matrix)
		ps_error(stack);
	ps_dup_argv_strings(stack, matrix, argv, argc);
	return (matrix);
}

void	ps_dup_argv_strings(t_stack *stack, char **matrix, char **argv, int argc)
{
	int	x;
	int	i;

	x = 0;
	while (x < argc - 1)
	{
		matrix[x] = ft_strdup(argv[x + 1]);
		if (!matrix[x])
		{
			i = 0;
			while (i < x)
				free(matrix[i++]);
			free(matrix);
			ps_error(stack);
		}
		x++;
	}
	matrix[x] = NULL;
}

int	*ps_validate_str_arr(t_stack *stack, char **str_arr, int *int_arr_len)
{
	int		x;
	int		*int_arr;

	x = 0;
	int_arr = ft_calloc(ps_strarr_len(str_arr), sizeof(int));
	if (!int_arr)
		ps_error(stack);
	x = ps_store_int_arr(stack, str_arr, int_arr, x);
	ps_check_duplicates(stack, int_arr, x);
	*int_arr_len = x;
	return (int_arr);
}

int	ps_store_int_arr(t_stack *stack, char **str_arr, int *int_arr, int x)
{
	int		y;
	long	num;

	while (str_arr[x])
	{
		y = 0;
		if (str_arr[x][y] == '-' || str_arr[x][y] == '+')
			y++;
		if (!str_arr[x][y])
			ps_error(stack);
		while (str_arr[x][y])
		{
			if (str_arr[x][y] < '0' || str_arr[x][y] > '9')
				ps_error(stack);
			y++;
		}
		num = ps_atol(str_arr[x]);
		ps_check_num(stack, int_arr, num);
		int_arr[x] = (int)num;
		x++;
	}
	return (x);
}

void ps_check_num(t_stack *stack, int *int_arr, long num)
{	
	if (num > 2147483647 || num < -2147483648)
		{
			free(int_arr);
			ps_error(stack);
		}
}
