/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:58:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/03/04 10:26:59 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"

int	dup_and_exec(t_pipex *cont, int input_fd, int output_fd, int i)
{
	if (cont->paths[i] == 0)
	{
		if (ft_strnstr(cont->cmds[i][0], "/", 1) != NULL)
			write_error(cont->cmds[i][0], "No such file or directory");
		else if (ft_strnstr(cont->cmds[i][0], "./", 2) != NULL)
			write_error(cont->cmds[i][0], "is a directory");
		else
			write_error(cont->cmds[i][0], "command not found");
		return (-1);
	}
	if (dup2(input_fd, STDIN_FILENO) == -1)
	{
		perror("Dup failed");
		return (-1);
	}
	if (dup2(output_fd, STDOUT_FILENO) == -1)
	{
		perror("Dup failed");
		return (-1);
	}
	close (input_fd);
	close (output_fd);
	if (execve(cont->paths[i], &cont->cmds[i][0], NULL) == -1)
		perror (cont->cmds[i][0]);
	return (-1);
}

int	infile_into_pipe(t_pipex *cont, int *fd, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror ("Failed to fork");
		return (-1);
	}
	if (pid == 0)
	{
		close(fd[0]);
		close (cont->fd_out);
		if (cont->fd_in > 0)
		{
			if (dup_and_exec(cont, cont->fd_in, fd[1], i) == -1)
			{
				close (fd[1]);
				exit(EXIT_FAILURE);
			}
		}
		exit(0);
	}
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
		perror ("Failed to fork");
		return (-1);
	}
	if (pid2 == 0)
	{
		close (fd[1]);
		if (dup_and_exec(cont, fd[0], cont->fd_out, i) == -1)
			exit(1);
		exit (EXIT_SUCCESS);
	}
	close(cont->fd_out);
	close(fd[0]);
	return (pid2);
}

int	cmd_pipe_cmd(t_pipex *cont, int *fd_pre, int i)
{
	pid_t	pid3;
	int		fd_npipe[2];

	if (pipe(fd_npipe) < 0)
		return (perror ("Failed to pipe"), -1);
	pid3 = fork();
	if (pid3 == -1)
		return (perror ("Failed to fork"), -1);
	if (pid3 == 0)
	{
		close(fd_pre[1]);
		close(fd_npipe[0]);
		if (dup_and_exec(cont, fd_pre[0], fd_npipe[1], i) == -1)
			exit (EXIT_FAILURE);
	}
	if (close (fd_pre[0]) == -1 || close (fd_npipe[1]) == -1)
		return (-1);
	dup2(fd_npipe[0], fd_pre[0]);
	dup2(fd_npipe[1], fd_pre[1]);
	close (fd_pre[1]);
	return (pid3);
}

int	piping(t_pipex *cont, int **pids, char **av)
{
	int	fd[2];
	int	i;

	i = 0;
	if (pipe(fd) == -1)
		return (perror("Failed to pipe"), -1);
	if (get_fdout(cont, av) != 0)
		return (-1);
	if (get_fdin(cont, av) != -1)
		(*pids)[i] = infile_into_pipe(cont, fd, i);
	i++;
	while (i < cont->cmd_count - 1)
	{
		(*pids)[i] = cmd_pipe_cmd(cont, fd, i);
		if ((*pids)[i] == -1)
			return (-1);
		i++;
	}
	if (cont->fd_out > 0)
		(*pids)[i] = pipe_into_outfile(cont, fd, i);
	(*pids)[++i] = 0;
	close (fd[1]);
	close (fd[0]);
	return (0);
}
