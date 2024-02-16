/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:06:34 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/16 14:12:13 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
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

void	free_struct(t_pipex *cont)
{
	free_3d_arr(cont->cmds);
	free_2d_arr(cont->paths);
	close(cont->fd_in);
	close (cont->fd_out);
	close (STDIN_FILENO);
	free (cont);
	exit (0);
}
