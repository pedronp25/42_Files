/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:00:41 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/18 22:42:29 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex *pp;

	pp = pipex_initializer(argc, argv);
	
	if (pipe(pp->pipe_fd) == -1)
		pipex_error("Error using pipe\n", pp);

	pp->id1 = fork();
	if (pp->id1 == -1)
		pipex_error("Error using fork\n", pp);
	
	if (pp->id1 == 0)
		child1(pp, argv[2], envp);

	pp->id2 = fork();
	if (pp->id2 == -1)
		pipex_error("Error using fork\n", pp);
	
	if (pp->id2 == 0)
		child2(pp, argv[3], envp);	
	
	waitpid(pp->id1, NULL, 0);
	waitpid(pp->id2, NULL, 0);

	pipex_cleanup(pp);
	return (EXIT_SUCCESS);
}
