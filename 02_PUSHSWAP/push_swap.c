/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:35:43 by pedromig          #+#    #+#             */
/*   Updated: 2025/08/17 04:35:47 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char *argv[])
{
	char	**str_arr;
	int		*int_arr;
	int		arr_len;
	t_stack	*stack;

	str_arr = ps_args_check(argc, argv);
	int_arr = ps_validate_str_arr(str_arr, &arr_len);
	ps_init_stacks(stack, int_arr, arr_len);
	if (stack->len_a <= 5)
		ps_smallstack_sort(stack);
	else
		ps_turk(stack);	
}
