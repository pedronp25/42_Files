/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 02:27:36 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/18 22:09:23 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child1(t_pipex *pp, char *cmd, char **envp)
{
	if (dup2(pp->fd1, STDIN_FILENO) == -1)
		pipex_error("Error using dup2", pp);
	close(pp->fd1);
	if (dup2(pp->pipe_fd[1], STDOUT_FILENO) == -1)
		pipex_error("Error using dup2", pp);
	close(pp->pipe_fd[1]);
	close(pp->pipe_fd[0]);
	pp->cmd1_args = ft_split(cmd, ' ');
	pp->cmd1_path = pipex_find_path(pp, envp);
	execve(pp->cmd1_path, pp->cmd1_args, envp);
}

void	child2(t_pipex *pp, char *cmd, char **envp)
{
	if (dup2(pp->pipe_fd[0], STDIN_FILENO) == -1)
		pipex_error("Error using dup2", pp);
	close(pp->pipe_fd[0]);
	if (dup2(pp->fd2, STDOUT_FILENO) == -1)
		pipex_error("Error using dup2", pp);
	close(pp->fd2);
	pp->cmd2_args = ft_split(cmd, ' ');
	pp->cmd2_path = pipex_find_path(pp, envp);
	execve(pp->cmd2_path, pp->cmd2_args, envp);
}

t_pipex	*pipex_initializer(int argc, char **argv)
{
	t_pipex *pp;	

	pp = ft_calloc(1, sizeof(t_pipex));
	if (!pp)
		pipex_error("Error allocating memory", pp);
	if (argc != 5)
		pipex_error("Usage: ./pipex.a infile 'cmd1' 'cmd2' outfile", pp);
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

char	*pipex_find_path(t_pipex *pp, char **envp)
{
	int		x;
	char	*path;
	int		len;

	len = ft_strlen("PATH=");
	x = 0;
	while (envp[x])
	{
		if(ft_strncmp(envp[x], "PATH=", len) == 0)
		{
			path = envp[x] + len;
			return (pipex_access_path(pp, path, pp->cmd1_args[0]));
		}
		x++;
	}
	pipex_error("Error finding command path", pp);
	return (NULL);
}

char	*pipex_access_path(t_pipex *pp, char *path, char *cmd)
{
	int		x;
	char	**path_args;
	char	*exe_path;
	char	*tmp_str;
	int		cmd_len;

	cmd_len = ft_strlen(cmd);
	path_args = ft_split(path, ':');
	x = 0;
	while (path_args[x])
	{
		tmp_str = ft_strjoin(path_args[x], "/");
		exe_path = ft_strjoin(tmp_str, cmd);
		free(tmp_str);
		if (access(exe_path, X_OK) == 0)
			return (pipex_free_arr(path_args), exe_path);
		free(exe_path);
		x++;
	}
	pipex_free_arr(path_args);
	pipex_error("Error finding command path", pp);
	return (NULL);
}
