/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:07:24 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/15 21:48:15 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>

typedef struct	s_pipex
{
	int		fd1;
	int		fd2;
	int		pipe_fd[2];
	int		id1;
	int		id2;
	char	**cmd1_args;
	char	**cmd2_args;
	char	**envp;
	char	*cmd1_path;
	char	*cmd2_path;
}	t_pipex;


void	child1(t_pipex *pp, char **argv, char **envp);
void	child2(t_pipex *pp, char **argv, char **envp);

#endif
