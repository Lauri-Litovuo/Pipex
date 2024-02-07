/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:41:47 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/07 12:55:30 by llitovuo         ###   ########.fr       */
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

static void	pipex(int fd_in, int fd_out, char **av, char **paths);
static void	child1_proc(int *fd, char **paths, char *cmd1);
static void	child2_proc(int *fd, char **paths, char *cmd2);
static void	free_array(char **arr);

int	main(int ac, char **av, char **envp)
{
	int			fd_in;
	int			fd_out;
	char		**paths;

	if (ac != 5) //change this to bonus < 5
	{
		write (2, "Too few arguments.\n", 19);
		return (-1);
	}
	check_permissions(av); //check what shell does when ofile does not exist then move this if it creates
	fd_in = open(av[1], O_RDONLY);
	fd_out = open(av[4], O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd_in == -1 || fd_out == -1)
		error_handling(7, NULL);
	paths = parse_path(envp);
	pipex(fd_in, fd_out, av, paths);
	free_array(paths);
	return (0);
}

static void	pipex(int fd_in, int fd_out, char **av, char **paths)
{
	int		fd[2];
	int		pid1;
	int		pid2;

	if (pipe(fd) == -1)
		error_handling(2, paths);
	pid1 = fork();
	if (pid1 == -1)
		error_handling(3, paths);
	if (pid1 == 0)
		child1_proc(fd, paths, av[2]);
	pid2 = fork();
	if (pid2 == -1)
		error_handling(2, paths);
	if (pid2 == 0)
		child2_proc(fd, paths, av[3]);
	if (close(fd[0]) == -1)
		handle_pipex_error(smth); //here somethign that I will pass
	if (close(fd[1]) == -1)
		handle_pipex_error(smth); //same here; struct?
	waitpid(pid1, NULL, 0); //check if waitpid error is needed
	waitpid(pid2, NULL, 0);
	return ;
}

static void	child1_proc(int *fd, char **paths, char *cmd1)
{
	int		i;
	char	*full_path;
	char	**cmds;
	
	i = 0;
	cmds = ft_split(cmd1, ' ');
	dup2(fd[1], STDOUT_FILENO);
	if (close(fd[0]) == -1)
		handle_pipex_error(smth); //here somethign that I will pass
	if (close(fd[1]) == -1)
		handle_pipex_error(smth); //same here; struct?
	// if (write(fd[1], &result, sizeof(result)) == -1)
	// {
	// 	perror("Writing to pipe failed: ")
	// 	exit (1);
	// }
	while (paths != 0)
	{
		full_path = join_str(paths[i], cmds[1]);
		if (!full_path)
		{
			free_array(cmds);
			error_handling(8, paths);
		}
		if (execve(full_path, cmds, paths) == -1)
			errors_in_child(paths, cmds);
		free(full_path);
		i++;
	}
	errors_in_child(paths, cmds);
}

static void	child2_proc(int *fd, char **paths, char *cmd2)
{
	int		i;
	char	*full_path;
	char	**cmds;

	i = 0;
	cmds = ft_split(cmd2, ' ');
	dup2(fd[0], STDIN_FILENO);
	if (close(fd[0]) == -1)
		handle_pipex_error(smth); //here somethign that I will pass
	if (close(fd[1]) == -1)
		handle_pipex_error(smth); //same here; struct?
	// if(read(fd[0],  &output_from_child, sizeof(output_from_child)) == -1);
	// {
	// 	perror("Writing to pipe failed: ")
	// 	exit (1);
	// }
	while (paths != 0)
	{
		full_path = join_str(paths[i], cmds[1]);
		if (!full_path)
		{
			free_array(cmds);
			error_handling(8, paths);
		}
		if (execve(full_path, cmds, paths) == -1)
			errors_in_child(paths, cmds);
		free (full_path);
		i++;
	}
}

static void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free (arr[i]);
		i++;
	}
	free (arr);
}
