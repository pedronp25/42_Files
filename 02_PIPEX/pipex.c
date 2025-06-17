/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:00:41 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/17 18:20:22 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex *pp;

	// Checks 'argc', initializes pp's variables 
		// and opens both fd's
	pp = pipex_initializer(argc, argv);
	
	if (pipe(pp->pipe_fd) == -1)
		pipex_error("Error using pipe", pp);

	pp->id1 = fork();
	if (pp->id1 == -1)
		pipex_error("Error using fork", pp);
	
	if (pp->id1 == 0)
		child1(pp, argv[2], envp);

	pp->id2 = fork();
	if (pp->id2 == -1)
		pipex_error("Error using fork", pp);
	
	if (pp->id2 == 0)
		child2(pp, argv[3], envp);	
	
	waitpid
	waitpid

}
