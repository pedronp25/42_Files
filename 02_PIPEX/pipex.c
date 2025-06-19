/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:00:41 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/20 00:29:11 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pp;

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
	close(pp->pipe_fd[0]);
	close(pp->pipe_fd[1]);
	waitpid(pp->id1, NULL, 0);
	waitpid(pp->id2, NULL, 0);
	pipex_cleanup(pp);
	return (EXIT_SUCCESS);
}

t_pipex	*pipex_initializer(int argc, char **argv)
{
	t_pipex	*pp;	

	if (argc != 5)
	{
		ft_printf("Usage: ./pipex infile 'cmd1' 'cmd2' outfile\n");
		exit(EXIT_FAILURE);
	}
	pp = ft_calloc(1, sizeof(t_pipex));
	if (!pp)
		pipex_error("Error allocating memory\n", pp);
	pp->pipe_fd[0] = -1;
	pp->pipe_fd[1] = -1;
	pp->id1 = -1;
	pp->id2 = -1;
	pp->fd1 = -1;
	pp->fd2 = -1;
	pp->fd1 = open(argv[1], O_RDONLY);
	if (pp->fd1 == -1)
		pipex_error("Error opening infile\n", pp);
	pp->fd2 = open(argv[4], O_WRONLY);
	if (pp->fd2 == -1)
		pipex_error("Error opening outfile\n", pp);
	return (pp);
}
