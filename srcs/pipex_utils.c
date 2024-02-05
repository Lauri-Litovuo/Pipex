/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:28:11 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/05 18:28:28 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

char	**parse_path(char **envp)
{
	char	**paths;
	char	*path_line;
	int		i;
	int		len;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 5) == NULL)
	{
		i++;
	}
	len = ft_strlen(envp[i]);
	path_line = ft_substr(envp[i], 5, len);
	if (path_line == NULL)
	{
		perror ("Error in parsing: ");
		exit (1);
	}
	paths = ft_split(path_line, ':');
	if (paths == NULL)
	{
		perror("Error in splitting envp: ");
		exit (1);
	}
	return (paths);
}

void	error_handling(int errcode)
{
	if (errcode == 2)
		perror ("Piping failed: ");
	if (errcode == 3)
		perror ("Fork pid1 failed: ");
	if (errcode == 4)
		perror ("Execve failed: ");
	if (errcode == 5)
		perror ("Fork pid2 failed: ");
	exit (1);
}