/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:15:04 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/07 16:50:03 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

void	error_handling(int errcode, char **paths)
{
	int	i;

	i = 0;
	if (errcode == 2)
		perror ("Piping failed: ");
	if (errcode == 3)
		perror ("Fork pid1 failed: ");
	if (errcode == 4)
		perror ("Execve failed: ");
	if (errcode == 5)
		perror ("Fork pid2 failed: ");
	if (errcode == 6)
		perror ("Split failed: ");
	if (errcode == 7)
		perror ("Error in opening file: ");
	if (errcode == 8)
		perror ("Error in joining: ");
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

void	check_permissions(char **av)
{
	if (access (av[1], F_OK))
		perror ("Infile not found: ");
	if (access(av[1], R_OK) == -1)
		perror ("Error in read permission: ");
	if (access(av[4], R_OK) == -1 || access(av[4], W_OK) == -1)
		perror ("Error in write permission: ");
	exit(1);
}

void	errors_in_child(char **paths, char **cmds)
{
	
}

void	free_cmds(char ***cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds[i] != NULL)
	{
		while (cmds[i][j] != NULL)
		{
			free(cmds[i][j]);
			j++;
		}
		free(cmds[i]);
		i++;
		j = 0;
	}
	free(cmds);
}
