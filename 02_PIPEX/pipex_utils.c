/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 02:27:36 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/17 00:49:19 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <fcntl.h>

void	child1(t_pipex *pp, char *cmd, char **envp)
{
	
}

void	child2(t_pipex *pp, char *cmd, char **envp)
{
	
}

t_pipex	*pipex_initializer(int argc, char **argv)
{
	t_pipex *pp;

	if (argc != 5)
		// Check Error (Wrong Argument Count)
	pp = ft_calloc(1, sizeof(t_pipex));
	if (!pp)
		// Check Error (Malloc Failed)
	pp->pipe_fd[0] = -1;
	pp->pipe_fd[1] = -1;
	pp->id1 = -1;
	pp->id2 = -1;
	pp->fd1 = -1;
	pp->fd2 = -1;
	pp->fd1 = open(argv[1], O_RDONLY);
		// Check Error (Open Failed)
	pp->fd2 = open(argv[4], O_WRONLY);
		// Check Error (Open Failed)
	return(pp);
}
