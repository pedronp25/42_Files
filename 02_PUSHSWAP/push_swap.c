/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:35:43 by pedromig          #+#    #+#             */
/*   Updated: 2025/08/21 19:38:40 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	if (stack->len_a <= 5)
		ps_smallstack_sort(stack);
	else
		ps_turk(stack);
}

void	ps_error(t_stack *stack)
{
	ft_printf("Error\n");
	ps_cleanup(stack);
	exit (1);
}

void	ps_success(t_stack *stack)
{
	ps_cleanup(stack);
	exit(0);
}

void	ps_cleanup(t_stack *stack)
{
	if (!stack)
		return ;
	ps_cleanup_stack(stack->a);
	ps_cleanup_stack(stack->b);
	free(stack);
}

void	ps_cleanup_stack(t_node *head)
{
	t_node	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}
