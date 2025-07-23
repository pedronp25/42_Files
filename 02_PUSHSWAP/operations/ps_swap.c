/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:05:13 by pedromig          #+#    #+#             */
/*   Updated: 2025/07/21 20:10:32 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	sa(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	first = stack->a;
	if (!first || !first->next)
		return ;
	second = first->next;
	first->next = second->next;
	second->next = first;
	stack->a = second; // New top is the second node
}

void	sb(t_stack *stack)
{
	t_node	*first;
	t_node	*second;

	first = stack->b;
	if (!first || !first->next)
		return ;
	second = first->next;
	first->next = second->next;
	second->next = first;
	stack->b = second; // New top is the second node
}

void	ss(t_stack *stack)
{
	sa(stack);
	sb(stack);
}
