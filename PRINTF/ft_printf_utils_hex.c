/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_hex.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 23:50:21 by pedromig          #+#    #+#             */
/*   Updated: 2025/05/06 00:50:58 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_hex(n, uppercase)
{
	int		size;
	char	*str;

	str = ft_hextoa(n, uppercase);
	if (!str)
		return (NULL);
	size = ft_putstr_size(str);
	return(free(str), size);
}
