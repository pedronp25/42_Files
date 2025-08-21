/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_validate_nums_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 07:21:24 by pedromig          #+#    #+#             */
/*   Updated: 2025/08/21 18:36:36 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	ps_strarr_len(char **str_arr)
{
	int	x;

	x = 0;
	while (str_arr && str_arr[x])
		x++;
	return (x);
}

long	ps_atol(const char *str)
{
	long	result;
	int		sign;

	sign = 1;
	result = 0;
	if (!str)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (sign * result);
}

void	ps_check_duplicates(t_stack *stack, int	*arr, int len)
{
	int	x;

	ps_quicksort_int_arr(arr, 0, len - 1);
	x = 0;
	while (x < len -1)
	{
		if (arr[x] == arr[x + 1])
			ps_error(stack);
		x++;
	}
}

void	ps_quicksort_int_arr(int *arr, int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = ps_partition(arr, low, high);
		ps_quicksort_int_arr(arr, low, pi - 1);
		ps_quicksort_int_arr(arr, pi + 1, high);
	}
}

int	ps_partition(int *arr, int low, int high)
{
	int	tmp;
	int	pivot;
	int	x;
	int	y;

	pivot = arr[high];
	x = low - 1;
	y = low;
	while (y < high)
	{
		if (arr[y] <= pivot)
		{
			x++;
			tmp = arr[x];
			arr[x] = arr[y];
			arr[y] = tmp;
		}
		y++;
	}
	ps_swap(&arr[x + 1], &arr[high]);
	return (x + 1);
}
