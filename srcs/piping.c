/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:55:51 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/13 14:34:13 by llitovuo         ###   ########.fr       */
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

int	dup_and_exec(t_pipex *cont, int input_fd, int output_fd, int i)
{
	if (cont->cmds[i][0] == 0)
		return (-1);
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("dup failed");
		return (-1);
	}
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		perror("dup failed");
		return (-1);
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
		if (dup_and_exec(cont, cont->fd_in, fd[1], i) == -1)
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
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror ("Fork failed");
		return (-1);
	}
	if (pid == 0)
	{
		if (close(fd[1]) == -1)
		{
			perror("close failed");
			return (-1);
		}
		if (dup_and_exec(cont, fd[0], cont->fd_out, i) == -1)
			return (-1);
	}
	else
	{
		close(cont->fd_out);
		close(fd[0]);
	}
	return (pid);
}

int	cmd_cmd_pipe(t_pipex *cont, int *fd, int i)
{
	pid_t	pid;
	int		fd2[2]; // fd[1], write ====== fd[0], read

	if (pipe(fd2) < 0)
	{
		perror ("pipe failed");
		return (-1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror ("fork failed");
		return (-1);
	}
	if (pid == 0)
	{
		close (fd2[0]);
		close (fd[1]);
		dup_and_exec(cont, fd[0], fd2[1], i);
	}
	dup2 (fd2[0], fd[0]);
	dup2 (fd2[1], fd[1]);
	close (fd2[0]);
	close (fd2[1]);
	return (pid);
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

