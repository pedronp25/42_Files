/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:29:41 by pedromig          #+#    #+#             */
/*   Updated: 2025/05/18 18:56:38 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list args;
	int	count;
	int	x;

	va_start(args, str);

	count = 0;
	x = 0;
	while (str[x]) //Iterate through string
	{
		if (str[x] == '%') //If it finds a '%'
		{
			count += condition_check(str[x+1], args); //Adds to the counter
														//Checks if the next char is valid
														//Prints the given argument
			x++;
		}
		else //If not a '%'
		{
			ft_putchar_fd(str[x], 1); //Simply prints the character in the string
			count++; //Adds to the counter
		}
		x++;
	}
	return (count); //Return the final character count
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
		size = ft_putunbr_size(va_arg(args, unsigned int));
	else if (c == 'p')
		size = ft_putptr(va_arg(args, void *));
	else if (c == 'x')
		size = ft_putnbr_hex(va_arg(args, unsigned int), 0);
	else if (c == 'X')
		size = ft_putnbr_hex(va_arg(args, unsigned int), 1);
	else
		return (-1);
	return (size);
}


int	main(void)
{
	char	c = 'a';
	char	*str = "This is a string";
	int		i = -1234;
	unsigned int	u = 1234;
	void	*p = &u;
	unsigned int	x = 1234;

	printf("Printf: %c\n%s\n%d\n%i\n%u\n%p\n%x\n%X\n%%\n", c, str, i, i, u, p, x, x);
	
	ft_putchar_fd('\n', 1);

	ft_printf("Ft_Printf: %c\n%s\n%d\n%i\n%u\n%p\n%x\n%X\n%%\n", c, str, i, i, u, p, x, x);
}

