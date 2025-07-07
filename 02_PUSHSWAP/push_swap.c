/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 20:35:43 by pedromig          #+#    #+#             */
/*   Updated: 2025/07/07 02:24:13 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include "libft/libft.h"

int	main(int argc, char *argv[])
{
	char	**matrix;

	matrix = ps_args_check(argc, argv);
	// Need to validate matrix (check ChatGPT)
}

char	**ps_args_check(int argc, char **argv)
{
	char	**matrix;
	int		x;

	if (argc == 1)
		exit (1);
	if (argc == 2)
	{
		matrix = ft_split(argv[1], ' ');
		if (!matrix)
			exit (1);
	}
	matrix = ft_calloc(argc - 1, sizeof(char));
	if (!matrix)
		exit (1);
	x = 1;
	while (x < argc)
	{
		matrix[x - 1] = argv[x];
		x++;
	}
	return (matrix);
}
