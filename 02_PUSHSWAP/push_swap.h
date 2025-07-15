/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:36:29 by pedromig          #+#    #+#             */
/*   Updated: 2025/07/15 02:06:20 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft/libft.h"

typedef struct s_node
{
	int				value;
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

#endif
