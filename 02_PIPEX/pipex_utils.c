/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 02:27:36 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/17 18:18:24 by pedromig         ###   ########.fr       */
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
		pipex_error("Usage: ./pipex.a infile 'cmd1' 'cmd2' outfile", pp);
	pp = ft_calloc(1, sizeof(t_pipex));
	if (!pp)
		pipex_error("Error allocating memory", pp);
	pp->pipe_fd[0] = -1;
	pp->pipe_fd[1] = -1;
	pp->id1 = -1;
	pp->id2 = -1;
	pp->fd1 = -1;
	pp->fd2 = -1;
	pp->fd1 = open(argv[1], O_RDONLY);
	if (pp->fd1 == -1)
		pipex_error("Error opening infile", pp);
	pp->fd2 = open(argv[4], O_WRONLY);
	if (pp->fd2 == -1)
		pipex_error("Error opening outfile", pp);
	return(pp);
}

void	pipex_error(char *err_msg, t_pipex *pp)
{
	perror(err_msg);
	pipex_cleanup(pp);
	exit(EXIT_FAILURE);
}

void	pipex_cleanup(t_pipex *pp)
{
	if (!pp)
		return ;
	if(pp->fd1 != -1)
		close(pp->fd1);
	if(pp->fd2 != -1)
		close(pp->fd2);
	if(pp->pipe_fd[0] != -1)
		close(pp->pipe_fd[0]);
	if(pp->pipe_fd[1] != -1)
		close(pp->pipe_fd[1]);
	// Free any allocated memory
		// (using a while loop, like the one used in ft_split)
	free(pp);
}
