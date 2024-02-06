/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:42:16 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/06 14:33:20 by llitovuo         ###   ########.fr       */
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

char	**parse_path(char **envp);
char	**parse_cmd(char **av);
char	*find_path(char **paths, char *cmd);
char	*join_str(char *path, char *cmd);
void	error_handling(int errcode, char **paths);
void	check_permissions(char **av);
void	errors_in_child(char **paths, char **cmds);


#endif
