/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:15:04 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/09 14:01:11 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

void	error_handling(int errcode, char **paths)
{
	int	i;

	i = 0;
	if (errcode == 2)
		perror ("pipex: Piping failed: ");
	if (errcode == 3)
		perror ("pipex: Fork pid1 failed: ");
	if (errcode == 4)
		perror ("pipex: Execve failed: ");
	if (errcode == 5)
		perror ("pipex: Fork pid2 failed: ");
	if (errcode == 6)
		perror ("pipex: Split failed: ");
	if (errcode == 7)
		perror ("pipex: Error in opening file: ");
	if (errcode == 8)
		perror ("pipex: Error in joining: ");
	if (paths != NULL)
	{
		while (paths[i] != NULL)
		{
			free(paths[i]);
			i++;
		}
		free (paths);
	}
	exit (1);
}

//these are checked to be right but there needs to be something to write these with. 
//Make sure the outfile is done even though av[1] fail
