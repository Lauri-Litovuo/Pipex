/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:55:51 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/16 17:46:47 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

int	dup_and_exec(t_pipex *cont, int input_fd, int output_fd, int i)
{
	if (cont->paths[i] == 0)
	{
		write_error(cont->cmds[i][0], "command not found");
		return (-1);
	}
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
		close(fd[0]);
		if (cont->fd_in > 0)
			dup_and_exec(cont, cont->fd_in, fd[1], i);
		close (cont->fd_in);
		close (fd[1]);
		return (-1);
	}
	else
	{
		if (cont->fd_in > 0)
			close(cont->fd_in);
		close(fd[1]);
	}
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

int	piping(t_pipex *cont, int **pids, char **av)
{
	int	fd[2];
	int	i;

	i = 0;
	if (pipe(fd) == -1)
	{
		perror("pipe failed");
		return (-1);
	}
	get_fdout(cont, av);
	if (get_fdin(cont, av) != -1)
		(*pids)[i] = infile_into_pipe(cont, fd, i);
	i++;
	if (cont->fd_out > 0)
		(*pids)[i] = pipe_into_outfile(cont, fd, i);
	(*pids)[++i] = 0;
	if ((*pids)[i - 1] == -1 || (*pids)[i - 2] == -1)
		return (-1);
	return (0);
}
