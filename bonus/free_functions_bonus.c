/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:58:37 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/15 13:50:23 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../incl/pipex_bonus.h"

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
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cont->cmds[i] != NULL)
	{
		while (cont->cmds[i][j] != NULL)
		{
			free(cont->cmds[i][j]);
			j++;
		}
		free(cont->cmds[i]);
		i++;
		j = 0;
	}
	free(cont->cmds);
	i = 0;
	while (cont->paths[i] != NULL)
	{
		free(cont->paths[i]);
		i++;
	}
	free(cont->paths);
	free(cont);
}
