/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:08:48 by pedromig          #+#    #+#             */
/*   Updated: 2025/05/01 23:17:06 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_size(int c)
{
	return(write(1, &c, 1));
}

int	ft_putstr_size(char *str)
{
	int	x;

	x = 0;
	while (s[x++])
		write(fd, &s[x], 1);
	return (x);
}

int	ft_putnbr_size(int i)
{
	char	*str;
	int		size;

	str = ft_itoa(i);
	if(!str)
		return (NULL);
	size = ft_putstr_size(str);
	return (free(str), size);
}

int	ft_putunbr_size(unsigned int u)
{
	char	*str;
	int		size;

	str = ft_uitoa(u);
	if (!str)
		return (NULL);
	size = ft_putstr_size(str);
	return(free(str), size);
}
