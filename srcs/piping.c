/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:55:51 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/09 16:56:18 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

/**
 * @brief 
 * 
 *  fd[1], write ====== fd[0], read
 * 
 * @param cont 
 * @param fd 
 * @param i 
 * @return int 
 */

int	dup_and_exec(t_pipex *cont, int fd, int i)
{
	if (cont->cmds[i][0] == 0)
		return (-1);
	if (i < 1)
	{
		if (dup2(cont->fd_in, STDIN_FILENO) == -1)
		{
			return (-1);
			perror("dup failed");
		}
	}
	else
	{
		if (dup2(STDOUT_FILENO, cont->fd_out) == -1)
		{
			perror("dup failed");
			return (-1);
		}
	}
	if (execve(cont->paths[i], cont->cmds[i][0], NULL) == -1)
		perror("execve failed");
	return (-1);
}


int	infile_pipe(t_pipex *cont, int *fd, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror ("Fork failed");
		return (-1);
	}
	if (pid == 0)
	{
		if (close(fd[0]) == -1)
		{
			perror("close failed");
			return (-1);
		}
		dup_and_exec(cont, fd[1], i);
		if (close(fd[1]) == -1)
			perror("close failed");
		return (-1);
	}
	else
	{
		close(cont->fd_in);
		close(fd[1]);
	}
	return (pid);
}

int	outfile_pipe(t_pipex *cont, int *fd, int i)
{
	
}

int	cmd_cmd_pipe(t_pipex *cont, int *fd, int i)
{
	
}

int	piping(t_pipex *cont, int **pids)
{
	int	fd[2];
	int	i;

	i = 0;
	if (pipe(fd) == -1)
	{
		free(fd);
		perror("pipe failed");
		return (-1);
	}
	(*pids)[i] = infile_pipe(cont, fd, i);
	if ((*pids)[i] == -1)
		return (-1);
	while (i < cont->cmd_count)
	{
		i++;
		(*pids)[i] = cmd_cmd_pipe(cont, fd, i);
		if ((*pids)[i] == -1)
			return (-1);
	}
	(*pids)[i] = outfile_pipe(cont, fd, i);
	if ((*pids)[i] == -1)
		return (-1);
	(*pids)[++i] = 0;
	return (0);
}

int	handle_processes(t_pipex *cont)
{
	pid_t	*pids;
	int		exitcode;

	pids = ft_calloc((cont->cmd_count + 1), sizeof(int));
	if (pids == 0)
		return (1);
	if (piping(cont, &pids) == -1)
	{
		free (pids);
		return (1);
	}
	exitcode = wait_children(pids);
	free(pids);
	return (exitcode);
}
