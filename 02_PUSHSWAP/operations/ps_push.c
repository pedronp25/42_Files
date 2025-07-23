/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 16:59:46 by pedromig          #+#    #+#             */
/*   Updated: 2025/07/23 17:05:35 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	pa(t_stack *stack)
{
	t_node	*node;

	if (!stack->b)
		return ;
	node = stack->b;
	stack->b = node->next;
	node->next = stack->a;
	stack->a = node;
	stack->len_a++;
	stack->len_b--;
}

void	pb(t_stack *stack)
{
	t_node	*node;

	if (!stack->a)
		return ;
	node = stack->a;
	stack->a = node->next;
	node->next = stack->b;
	stack->b = node;
	stack->len_b++;
	stack->len_a--;
}
