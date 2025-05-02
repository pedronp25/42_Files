/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:29:41 by pedromig          #+#    #+#             */
/*   Updated: 2025/05/01 23:24:24 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list args;
	int	count;

	va_start(args, str);

	count = 0;
	while (str[x])
	{
		if (str[x] == '%')
		{
			count += condition_check(str[x+1], args);
			x++;
		}
		else
		{
			ft_putchar_fd(str[x], 1);
			count++;
		}
		x++;
	}
	
}

int	condition_check(char c, va_list args)
{
	int	size;

	if (c == '%')
		size = ft_putchar_size('%');
	else if (c == 'c')
		size = ft_putchar_size(va_arg(args, int));
	else if (c == 's')
		size = ft_putstr_size(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		size = ft_putnbr_size(va_arg(args, int));
	else if (c == 'u')
		size = ft_putunbr_size(va_arg(args, unsigned int);
	else if (c == 'p')
		
	else if (c == 'x')
		
	else if (c == 'X')
		
	else
		return (-1);
	return (size);
}

/*
int	main(void)
{
	char	c = 'a';
	char	*str = "This is a string";
	int		i = -1234;
	unsigned int	u = 1234;

	printf("Printf: %c\n
		%s\n
		%d\n
		%i\n
		%u\n
		%%\n"
		, c, str, i, i, u);
	
	ft_putchar_fd('\n', 1);

	ft_printf("Ft_Printf: %c\n
		%s\n
		%d\n
		%i\n
		%u\n
		%%\n"
		, c, str, i, i, u);
}
*/
