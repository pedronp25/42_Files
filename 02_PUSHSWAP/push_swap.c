/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:35:43 by pedromig          #+#    #+#             */
/*   Updated: 2025/07/15 02:08:52 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char *argv[])
{
	char	**str_arr;
	int		*int_arr;
	int		arr_len;
	t_stack	stack;

	str_arr = ps_args_check(argc, argv);
	int_arr = ps_validate_str_arr(str_arr, &arr_len);
	ps_init_stacks(&stack, int_arr, arr_len);
}

void	ps_init_stacks(t_stack *stack, int *int_arr, int len)
{
	int	x;

	x = 0;
	while (x < len)
	{
		// Create a node for each value (needs a function to create each node)
	}
	stack->b = NULL;
	stack->len_a = len;
	stack->len_b = 0;
}
