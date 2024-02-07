/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:28:11 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/07 15:04:56 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

char	**parse_path(char **envp)
{
	char	**paths;
	char	*path_line;
	int		i;
	int		len;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 5) == NULL)
	{
		i++;
	}
	len = ft_strlen(envp[i]);
	path_line = ft_substr(envp[i], 5, len);
	if (path_line == NULL)
	{
		perror ("Error in parsing: ");
		exit (1);
	}
	paths = ft_split(path_line, ':');
	if (paths == NULL)
		error_handling(6, paths);
	return (paths);
}

char	**get_cmds(int ac, char **av)
{
	char	**cmds;
	int		cmd_count;
	int		i;

	i = 0;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		cmd_count = ac - 3;
	else
		cmd_count = ac - 2;
	cmds = (char **) malloc((cmd_count + 1) * sizeof(char **));
	if (!cmds)
		return (NULL);
	while (i < cmd_count)
	{
		cmds[i] = ft_strdup(av[i + 2]);
		i++;
	}
	cmds[i] = 0;
	i = 0;
	return (cmds);
}

char	*find_path(char **paths, char *cmd)
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

char	*join_str(char *path, char *cmd)
{
	char	*joint;
	int		len;

	if (!path || !cmd)
		return (NULL);
	len = ft_strlen((char *)path);
	len += ft_strlen((char *)cmd);
	joint = (char *) malloc(len * sizeof(char) + 2);
	if (!(joint))
		return (NULL);
	ft_strlcpy(joint, path, len + 2);
	ft_strlcat(joint, "/", len + 2);
	ft_strlcat(joint, cmd, len + 2);
	return (joint);
}