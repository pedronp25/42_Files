/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:00:41 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/17 00:49:17 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex *pp;

	// Checks 'argc', initializes pp's variables and opens both fd's
	pp = pipex_initializer(argc, argv);
	
	pipe(pp->pipe_fd);
		//Check Error (Pipe Failed)

	pp->id1 = fork();
		//Check Error (Fork Failed)
	
	if (pp->id1 == 0)
		child1(pp, argv[2], envp);

	pp->id2 = fork();
		//Check Error (Fork Failed)
	
	if (pp->id2 == 0)
		child2(pp, argv[3], envp);	
	
}
