/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:00:41 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/15 22:15:23 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex *pp;

	// Check argc

	pipex_initializer(argv); // NOT DONE
		//pp = ft_calloc(1, sizeof(t_pipex)); --> TO ADD INSIDE THE FUNCTION
	
	pp->fd1 = open(argv[1], O_RDONLY);
	// Check open
	pp->fd2 = open(argv[4], O_WRONLY);
	// Check open

	pipe(pp->pipe_fd);
	//Check pipe

	pp->id1 = fork();
	//Check fork
	
	if (pp->id1 == 0)
		child1(pp, argv[2], envp);

	pp->id2 = fork();
	//Check fork
	
	if (pp->id2 == 0)
		child2(pp, argv[3], envp);	
	
}
