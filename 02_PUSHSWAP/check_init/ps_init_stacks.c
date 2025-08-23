/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_init_stacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:29:41 by pedromig          #+#    #+#             */
/*   Updated: 2025/08/24 00:11:39 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_stack	*ps_init_stacks(int *int_arr, int len)
{
	int		x;
	t_node	*new_node;
	t_stack	*stack;

	stack = ft_calloc(1, sizeof(t_stack));
	if (!stack)
		ps_error(stack);
	stack->a = NULL;
	x = 0;
	while (x < len)
	{
		new_node = ps_new_node(stack, int_arr[x]);
		ps_node_add_back(&stack->a, new_node);
		x++;
	}
	stack->b = NULL;
	stack->len_a = len;
	stack->len_b = 0;
	return (stack);
}

t_node	*ps_new_node(t_stack *stack, int value)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		ps_error(stack);
	node->value = value;
	node->next = NULL;
	return (node);
}

void	ps_node_add_back(t_node **head, t_node *new_node)
{
	t_node	*last_node;

	if (!new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	last_node = *head;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = new_node;
}
