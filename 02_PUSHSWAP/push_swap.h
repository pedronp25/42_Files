/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:36:29 by pedromig          #+#    #+#             */
/*   Updated: 2025/08/11 18:35:40 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

typedef struct s_node
{
	int				value;
	int				cost_a;
	int				cost_b;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*a; // Top of stack A
	t_node	*b; // Top of stack B
	int		len_a;
	int		len_b;
}	t_stack;

char	**ps_args_check(int argc, char **argv);
int		*ps_validate_str_arr(char **str_arr, int *int_arr_len);
int		ps_strarr_len(char **str_arr);
void	ps_check_duplicates(int	*arr, int len);
void	ps_init_stacks(t_stack *stack, int *int_arr, int len);
t_node	*ps_new_node(int value, int index);
void	ps_node_add_back(t_node **lst, t_node *new_node);
void	pa(t_stack *stack);
void	pb(t_stack *stack);
void	sa(t_stack *stack);
void	sb(t_stack *stack);
void	ss(t_stack *stack);
void	ra(t_stack *stack);
void	rb(t_stack *stack);
void	rr(t_stack	*stack);
void	rra(t_stack *stack);
void	rrb(t_stack *stack);
void	rrr(t_stack	*stack);
void	ps_smallstack_sort(t_stack *stack);
int		ps_find_min_pos(t_node	*node);
void	ps_rotate_to_top(t_stack *stack, int pos);
void	ps_sort_2(t_stack *stack);
void	ps_sort_3(t_stack *stack);
void	ps_sort_4(t_stack *stack);
void	ps_sort_5(t_stack *stack);
void	ps_calculate_cost(t_stack *stack);
int		ps_get_cost_b(t_stack *stack, int pos);
int		ps_get_target_pos_a(t_stack *stack, int b_val);
int		ps_find_smallest_value(t_node *current);
int		ps_get_cost_a(t_stack *stack, int target_pos);

#endif
