/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:29:41 by pedromig          #+#    #+#             */
/*   Updated: 2025/04/30 23:22:14 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LIBFT/libft.h" // Check if correct

int	ft_printf(const char *str, ...)
{
	va_list args;

	va_start(args, str);

	while (str[x])
	{
		if (str[x] == '%')
		{
			condition_check(str[x+1], args);
			x++;
		}
		else
			ft_putchar_fd(str[x], 1);
		x++;
	}
}

void	condition_check(char c, va_list args)
{
	if (c == '%')
		ft_putchar_fd('%', 1);
	else if (c == 'c')
		ft_putchar_fd(va_arg(args, char), 1);
	else if (c == 's')
		ft_putstr_fd(va_arg(args, char *), 1);
	else if (c == 'd' || c == 'i')
		ft_putnbr_fd(va_arg(args, int), 1);
	else
		return ;
}

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
