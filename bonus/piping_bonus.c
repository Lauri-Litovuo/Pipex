/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:58:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/15 13:50:39 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"

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
	execve(cont->paths[i], &cont->cmds[i][0], NULL);
	perror(cont->cmds[i][0]);
	return (-1);
}

int	infile_into_pipe(t_pipex *cont, int *fd, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror ("Fork failed");
		return (1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		if (cont->fd_in > 0)
		{
			if (dup_and_exec(cont, cont->fd_in, fd[1], i) == -1)
			{
				close (fd[1]);
				exit(EXIT_FAILURE);
			}
		}
		exit(EXIT_SUCCESS);
	}
	if (cont->fd_in > 0)
		close(cont->fd_in);
	close(fd[1]);
	return (pid);
}

int	pipe_into_outfile(t_pipex *cont, int *fd, int i)
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 == -1)
	{
		perror ("Fork failed");
		return (-1);
	}
	if (pid2 == 0)
	{
		close (fd[1]);
		if (dup_and_exec(cont, fd[0], cont->fd_out, i) == -1)
			exit(EXIT_FAILURE);
		exit (EXIT_SUCCESS);
	}
	close(cont->fd_out);
	close(fd[0]);
	return (pid2);
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
	if (get_fdout(cont, av) != 0)
		return (-1);
	if (get_fdin(cont, av) != -1)
		(*pids)[i] = infile_into_pipe(cont, fd, i);
		while (++i < cont->cmd_count - 1)
	{
		(*pids)[i] = cmd_pipe_cmd(cont, fd, i);
		if ((*pids)[i] == -1)
			return (-1);
	}
	if (cont->fd_out > 0)
		(*pids)[i] = pipe_into_outfile(cont, fd, i);
	i++;
	(*pids)[i] = 0;
	close (fd[1]);
	close (fd[0]);
	if ((*pids)[i - 1] != 0 || (*pids)[i - 2] != 0)
		return (-1);
	return (0);
}
