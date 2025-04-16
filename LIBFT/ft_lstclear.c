/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:08:51 by pedromig          #+#    #+#             */
/*   Updated: 2025/04/17 00:24:17 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*node_ptr;

	if (!lst)
		return ;
	node_ptr = *lst;
	while (node_ptr)
	{
		ft_lstdelone(node_ptr, del);
		node_ptr = node_ptr->next;
	}
	*lst = NULL;
}
