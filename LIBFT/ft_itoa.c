/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 22:57:02 by pedromig          #+#    #+#             */
/*   Updated: 2025/04/13 00:03:25 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	int_size(int n);

char	*ft_itoa(int n)
{
	int	x;
	char	*str;

	x = 0;
	str = malloc(int_size(n));
	if (!str)
		return (NULL);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		str[x] = '-';
		n = -n;
		x++;
	}
	if ()
}

int	int_size(int n)
{
	int	x;

	x = 0;
	while (n > 0)
	{
		n /= 10;
		x++;
	}
	return (x);
}


