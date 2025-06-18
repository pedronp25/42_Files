/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromig <pedromig@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:36:07 by pedromig          #+#    #+#             */
/*   Updated: 2025/06/19 00:35:24 by pedromig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

void	pipex_error(char *err_msg, t_pipex *pp)
{
	ft_printf("%s", err_msg);
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
	//if(pp->pipe_fd[0] != -1)
	close(pp->pipe_fd[0]);
	//if(pp->pipe_fd[1] != -1)
	close(pp->pipe_fd[1]);
	// Free any allocated memory
		// (using a while loop, like the one used in ft_split)
	//pipex_free_arr(pp->cmd1_args);
	free(pp);
}

void	pipex_free_arr(char **arr)
{
	int	x;

	x = 0;
	while (arr[x])
	{
		free(arr[x]);
		x++;
	}
	free(arr);
}
