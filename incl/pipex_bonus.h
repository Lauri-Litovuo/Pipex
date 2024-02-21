/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauri <lauri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:42:16 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/21 12:51:46 by lauri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>

typedef struct s_pipex
{
	int				fd_in;
	int				fd_out;
	char			**paths;
	char			***cmds;
	int				cmd_count;
	int				here_doc;
}				t_pipex;

char	**get_paths(char ***cmds, int cmd_count, char **envp);
char	**parse_path(char **envp);
char	*find_path(char *cmd, char **env_paths);

int		count_cmds(int ac, char **av);
char	***get_cmds(char **av, int cmd_count);

int		get_fdin(t_pipex *cont, char **av);
int		get_fdout(t_pipex *cont, char **av);
void	write_error(char *name, char *errmsg);

void	free_2d_arr(char **arr);
void	free_3d_arr(char ***arr);
void	free_paths(char **paths, int path_count);
void	free_struct(t_pipex *cont);

int		dup_and_exec(t_pipex *cont, int input_fd, int output_fd, int i);
int		infile_into_pipe(t_pipex *cont, int *fd, int i);
int		pipe_into_outfile(t_pipex *cont, int *fd, int i);
int		cmd_pipe_cmd(t_pipex *cont, int *fd_pre, int i);
int		piping(t_pipex *cont, int **pids, char **av);
char	*join_str(char *path, char *cmd);

int		handle_processes(t_pipex *cont, char **av);
int		wait_children(pid_t *pids);

void handle_heredoc(t_pipex *cont, char **av);

#endif
