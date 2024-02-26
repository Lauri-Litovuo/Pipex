/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:06:34 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/26 14:30:28 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_3d_arr(char ***arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arr[i] != NULL)
	{
		while (arr[i][j] != NULL)
		{
			free(arr[i][j]);
			j++;
		}
		free(arr[i]);
		i++;
		j = 0;
	}
	free(arr);
}

void	free_paths(char **paths, int path_count)
{
	while (path_count > 0)
	{
		if (paths[path_count -1] != NULL)
			free(paths[path_count - 1]);
		path_count--;
	}
	free(paths);
}

void	free_struct(t_pipex *cont)
{
	free_3d_arr(cont->cmds);
	free_paths(cont->paths, cont->cmd_count);
	close(cont->fd_in);
	close (cont->fd_out);
	close (STDIN_FILENO);
	free (cont);
	exit (0);
}
