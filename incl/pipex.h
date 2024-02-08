/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:42:16 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/08 16:17:34 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
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
	int				here_doc; // for bonus
}				t_pipex;

char	**get_paths(char ***cmds, int cmd_count, char **envp);
char	**parse_path(char **envp);
char	*find_path(char *cmd, char **env_paths);

int		count_cmds(int ac, char **av);
char	***get_cmds(char **av, int cmd_count);

void	free_2d_arr(char **arr);
void	free_3d_arr(char ***arr);
void	free_struct(t_pipex *cont);

char	*join_str(char *path, char *cmd);
void	error_handling(int errcode, char **paths);
void	check_permissions(char **av);
void	errors_in_child(char **paths, char **cmds);
void	free_struct(t_pipex *cont);

#endif
