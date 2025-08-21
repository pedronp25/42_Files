/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_find_cheapest_node.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 03:30:28 by pedromig          #+#    #+#             */
/*   Updated: 2025/08/21 18:06:03 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

t_node	*ps_find_cheapest_node(t_node *current)
{
	t_node	*cheapest_node;
	int		lowest_cost;
	int		total_cost;

	cheapest_node = current;
	lowest_cost = ps_abs(current->cost_a) + ps_abs(current->cost_b);
	current = current->next;
	while (current)
	{
		total_cost = ps_abs(current->cost_a) + ps_abs(current->cost_b);
		if (total_cost < lowest_cost)
		{
			lowest_cost = total_cost;
			cheapest_node = current;
		}
		current = current->next;
	}
	return (cheapest_node);
}

int	ps_abs(int value)
{
	if (value < 0)
		return (-value);
	return (value);
}
