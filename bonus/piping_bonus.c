/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:58:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/14 14:59:14 by llitovuo         ###   ########.fr       */
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
		perror("input dup failed");
		return (-1);
	}
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		perror("output dup failed");
		return (-1);
	}
	if (execve(cont->paths[i], &cont->cmds[i][0], NULL) == -1)
		perror("execve failed");
	return (-1);
}


int	infile_into_pipe(t_pipex *cont, int *fd, int i)
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
			perror("infile close failed");
			return (-1);
		}
		if (dup_and_exec(cont, cont->fd_in, fd[1], i) == -1)
			return (-1);
	}
	else
	{
		close(cont->fd_in); //fdf[0]
		close(fd[1]);
	}
	//printf("pid infile: %d\n", pid); //delete
	return (pid);
}

int	pipe_into_outfile(t_pipex *cont, int *fd, int i)
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
		close (fd[1]);
		//printf("cont outfile: %d\n", cont->fd_out); //delete
		if (dup_and_exec(cont, fd[0], cont->fd_out, i) == -1)
			return (-1);
	}
	else
	{
		close(fd[0]);
		close(cont->fd_out);
	}
	//printf("pid outfile: %d\n", pid); //delete
	return (pid);
}

int	cmd_pipe_cmd(t_pipex *cont, int *fd_pre, int i)
{
	pid_t	pid;
	int		fd_npipe[2];

	if (pipe(fd_npipe) < 0)
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
		if (close (fd_pre[1]) == -1 || close (fd_npipe[0]))
			return (-1);
		dup_and_exec(cont, fd_pre[0], fd_npipe[1], i);
	}
	else
	{
		if (close (fd_pre[0]) == -1 || close (fd_npipe[1]) == -1)
			return (-1);
		fd_pre[0] = fd_npipe[0];
		fd_pre[1] = fd_npipe[1];
	}
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
	(*pids)[i] = infile_into_pipe(cont, fd, i);
	if ((*pids)[i] == -1)
		return (-1);
	while (++i < cont->cmd_count - 1)
	{
		//printf("not here %d\n", i); //delete
		(*pids)[i] = cmd_pipe_cmd(cont, fd, i);
		if ((*pids)[i] == -1)
			return (-1);
	}
	(*pids)[i] = pipe_into_outfile(cont, fd, i);
	if ((*pids)[i] == -1)
		return (-1);
	(*pids)[++i] = 0;
	return (0);
}

