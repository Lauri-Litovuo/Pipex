/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 12:15:04 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/08 17:51:42 by llitovuo         ###   ########.fr       */
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
void	file_errors(char **av)
{
	if (access (av[1], F_OK))
	{
		perror ("pipex: no such file or directory: ");
		ft_putstr_fd(av[1], 2);
		ft_putchar_fd("\n", 2);
	}
	if (access(av[1], R_OK) == -1)
		perror ("pipex: permission denied: %s", av[1]);
	if (access(av[4], R_OK) == -1 || access(av[4], W_OK) == -1)
		perror ("pipex: permission denied: %s\n", av[4]);
	exit(1);
}