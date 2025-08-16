/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sort_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 19:45:47 by pedromig          #+#    #+#             */
/*   Updated: 2025/07/29 19:48:44 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ps_sort_2(t_stack *stack)
{
	if (stack->a->value > stack->a->next->value)
		sa(stack);
}

void	ps_sort_3(t_stack *stack)
{
	int	a;
	int	b;
	int	c;

	a = stack->a->value;
	b = stack->a->next->value;
	c = stack->a->next->next->value;
	if (a > b && b < c && a < c) // 2 1 3
		sa(stack);
	else if (a > b && b > c) // 3 2 1
	{
		sa(stack);
		rra(stack);
	}
	else if (a > b && b < c && a > c) // 2 3 1
		ra(stack);
	else if (a < b && b > c && a < c) // 1 3 2
	{
		sa(stack);
		ra(stack);
	}
	else if (a < b && b > c && a > c) // 3 1 2
		rra(stack);
}

void	ps_sort_4(t_stack *stack)
{
	int	pos;

	pos = ps_find_min_pos(stack->a);
	ps_rotate_to_top(stack, pos);
	pb(stack);
	ps_sort_3(stack);
	pa(stack);
}

void	ps_sort_5(t_stack *stack)
{
	int	pos;

	pos = ps_find_min_pos(stack->a);
	ps_rotate_to_top(stack, pos);
	pb(stack);
	ps_sort_4(stack);
	pa(stack);
}
