/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 23:42:11 by pedromig          #+#    #+#             */
/*   Updated: 2025/08/23 23:43:10 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
