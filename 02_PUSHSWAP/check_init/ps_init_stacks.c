/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_init_stacks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:29:41 by pedromig          #+#    #+#             */
/*   Updated: 2025/07/29 19:48:06 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ps_init_stacks(t_stack *stack, int *int_arr, int len)
{
	int	x;
	t_node	*new_node;
	
	stack->a = NULL;
	x = 0;
	while (x < len)
	{
		new_node = ps_new_node(int_arr[x], x);
		ps_node_add_back(&stack->a, new_node);
		x++;
	}
	stack->b = NULL;
	stack->len_a = len;
	stack->len_b = 0;
}

t_node	*ps_new_node(int value, int index)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		exit (1);
	node->value = value;
	node->next = NULL;
	return (node);
}

void	ps_node_add_back(t_node **lst, t_node *new_node)
{
	t_node	*last_node;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	last_node = *lst;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = new_node;
}
