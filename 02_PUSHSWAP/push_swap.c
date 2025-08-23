/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:35:43 by pedromig          #+#    #+#             */
/*   Updated: 2025/08/23 23:57:40 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

int	main(int argc, char *argv[])
{
	char	**str_arr;
	int		*int_arr;
	int		arr_len;
	t_stack	*stack;

	stack = NULL;
	str_arr = ps_args_check(stack, argc, argv);
	int_arr = ps_validate_str_arr(stack, str_arr, &arr_len);
	stack = ps_init_stacks(int_arr, arr_len);
	if (ps_sorted(stack))
		ps_success(stack);
	else if (stack->len_a <= 5)
		ps_smallstack_sort(stack);
	else
		ps_turk(stack);
	ps_success(stack);
}

int	ps_sorted(t_stack *stack)
{
	t_node	*current;

	current = stack->a;
	while (current->next)
	{
		if (current->value > current->next->value)
			return (0);
		current = current->next;
	}
	return (1);
}
