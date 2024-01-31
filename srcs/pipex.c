/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:41:47 by llitovuo          #+#    #+#             */
/*   Updated: 2024/01/31 14:59:24 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"
/**
 * @brief 
 * 
 * @param ac 
 * @param av These should be:
 * 				av[0] = pipex.c, 
 *				av[1] = file1, 
 * 				av[2] = cmd1, 
 * 				av[3] = cmd2, 
 * 				av[4] = file2
 * 
 * @return int 
 */


int	main(int ac, char **av)
{
	int		*pids;
	int		cmd_count;
	pid_t	wait_status;
	int		status;
	int		i;

	i = 0;
	cmd_count = ac - 2 - 1;
	check_for_errors(ac, av);
	// if (ft_strncmp(av[1], "here_doc", 9);
	// 	i = ac - 1 - 2
	if (pid == -1)
	{
		perror("Fork failed: ");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) //child process to exevute
	{
		exec_child(av[1], av[2]);
		
	}
	else //the parent process
	{
		wait_status = waitpid(pid, &status, );
		if (wait_status == -1)
		{
			perror("Waitpid failed: ");
			exit (EXIT_FAILURE);	
		}
		pipe_child_outcome();
	}
	cmd_count = ac - 1 - 2;
	while (i < cmd_count)
		create_childs;

}


void	create_childs(int ac)
{
	pid_t	pid;
	int		fd[2]; // fd[1], write ====== fd[0], read
	
	if (pipe(fd) == -1)
	{
		perror("Error in opening pipe: ");
		exit (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed: ");
		exit (1);
	}
	if (pid == 0) //child
	{
		char *result;
		close(fd[0]);
		if (write(fd[1], &result, sizeof(result)) == -1)
		{
			perror("Writing to pipe failed: ")
			exit (1);
		}
		
		close (fd[1]);
	}
	else //parent
	{
		char *output_from_child;
		close(fd[1]);
		if(read(fd[0],  &output_from_child, sizeof(output_from_child)) == -1);
		{
			perror("Writing to pipe failed: ")
			exit (1);
		}
		close(fd[0]);
	}

	
	
}

check_for_errors(int ac, char **av)
{
	if (ac < 5)
	{
		write (2, "Too few arguments.\n", 19);
		return (-1);
	}
	// if (access (av[1], F_OK) && access(av[4], F_OK))
	// 	perror ("File not found: ");
	// if (access(av[1], R_OK) == -1)
	// 	perror ("Error in file: ");
	// if (access(av[4], W_OK) == -1)
	// 	perror ("Error in file: ");
	if ()
}

	// int		fd_f1;
	// int		fd_f2;
	
	// fd_f1 = open (av[1], O_RDONLY);
	// fd_f2 = open (av[4], O_WRONLY);