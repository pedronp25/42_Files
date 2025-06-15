/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:00:41 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/15 21:53:16 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex *pp;

	// Check argc

	pp = ft_calloc(1, sizeof(t_pipex));
	// Check calloc
	
	pp->fd1 = open(argv[1], O_RDONLY);
	// Check open
	pp->fd2 = open(argv[4], O_WRONLY);
	// Check open

	pipe(pp->pipe_fd);
	//Check pipe

	pp->id1 = fork()
	//Check fork
	
	if (pp->id1 == 0)
		child_process(pp->fd1, pp->pipe_fd[1],
				pp->pipe_fd[0], argv[2], envp);

	pp->id2 = fork()
	//Check fork
	
	if (pp->id2 == 0)
		child_process(pp->pipe_fd[0], pp->fd2,
				pp->pipe_fd[1], argv[3], envp);	
	
}
