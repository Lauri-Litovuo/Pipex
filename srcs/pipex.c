/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:41:47 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/05 18:27:49 by llitovuo         ###   ########.fr       */
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
	int			cmd_count;
	int			i;
	extern char	**environ;
	char		*path;

	i = 0;
	cmd_count = ac - 2 - 1;
	get_path = environ;
	// if (ft_strncmp(av[1], "here_doc", 9);
	// 	i = ac - 1 - 1;
	if (ac != 5) //change this to bonus < 5
	{
		write (2, "Too few arguments.\n", 19);
		return (-1);
	}
	the_pipe(cmd_count, av, NULL);
}

//Function functions similar to pipe operator
void the_pipe(int ac, char *cmd, char **envp)
{
	int	fd[2];
	int	pid1;
	int	pid2;
	int	err;

	if (pipe(fd) == -1)
		error_handling(2);
	pid1 = fork();
	if (pid1 == -1)
		error_handling(3);
	if (pid1 == 0)
	{ //first child process
		dup2(fd[1], STDOUT_FILENO);
		close (fd[0]);
		close (fd[1]);
		err = (execve("the path", cmd, envp));
		if (err == -1)
			error_handling(4);
	}
	pid2 = fork();
	if (pid2 == -1)
		error_handling(2);
	if (pid2 == 0)
	{ //second child process
		dup2(fd[0], STDIN_FILENO);
		close (fd[0]);
		close (fd[1]);
		err = (execve("the path", cmd, envp));
		if (err == -1)
			error_handling(4);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return ;
}

//This works and parses


/*

char	*get_path(char **env)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i] != 0)
	{
		full_path = ft_strjoin("/", cmd);
		full_path = ft_strjoin(paths[i], cmd);
		if (access(full_path, F_OK) == 0)
			return (paths[i]);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	pipe_fork(int cmd_count, char **av, char **paths)
{
	int	pids[cmd_count];
	int	pipes[cmd_count + 1][2];
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cmd_count + 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror ("Piping failed: ");
			exit (1);
		}
		i++;
	}
	i = 0;
	while (i < cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == - 1)
		{
			perror ("Fork failed: ");
			exit (1);
		}
		if (pids[i] == 0)
		{
			if (pids[i] == 0)
			{
				if (i != j)
					close (pipes[j][0]);
				if (i + 1 != j)
					close (pipes[j][1]);
			}
		}
	}
}*/

/*
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
		wait()
	}
}



	// int		fd_f1;
	// int		fd_f2;
	
	// fd_f1 = open (av[1], O_RDONLY);
	// fd_f2 = open (av[4], O_WRONLY);


/* This snippet kind of dups the file_fd of stdout so I can write to file

	int file;
	int fd_writeto;
	int err;

	if (pid == 0)
	{
		file = open ("outputfile.txt", O_WRONLY);
		if (file == - 1)
		{
			perror("smth");
			exit(1);
		}
	}
	file = dup2(file, 1 || STDOUT_FILENO);
	close (file);

	*here the code that calls ls etc. e.g.:
	if (pid == 0)
	{
		err (execve(vector, env))
		if (err == -1)
		{
			perror("smth");
			exit (1);
		}
	}
	else
	{
		smth
	}
		
	}*/
/*
		if (access (av[1], F_OK) && access(av[4], F_OK))
		perror ("File not found: ");
	else if (access(av[1], R_OK) == -1)
		perror ("Error in file: ");
	else if (access(av[4], W_OK) == -1)
		perror ("Error in file: ");