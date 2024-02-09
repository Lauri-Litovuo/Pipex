/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:53:38 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/09 10:42:33 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

char	**parse_path(char **envp);
char	*find_path(char *cmd, char **env_paths);

char	**get_paths(char ***cmds, int cmd_count, char **envp)
{
	int		i;
	char	**env_paths;
	char	**paths;

	i = 0;
	env_paths = parse_path(envp);
	if (!env_paths)
		return (NULL);
	paths = (char **) malloc ((cmd_count + 1) * sizeof(char **));
	while (i < cmd_count)
	{
		paths[i] = find_path(cmds[i][0], env_paths);
		i++;
	}
	paths[i] = 0;
	free_2d_arr(env_paths);
	return (paths);
}

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
		return (NULL);
	paths = ft_split(path_line, ':');
	if (!paths)
		return (free(path_line), NULL);
	return (free(path_line), paths);
}

char	*find_path(char *cmd, char **env_paths)
{
	int		i;
	char	*temp;
	char	*full_path;

	i = 0;
	temp = ft_strjoin("/", cmd);
	if (!temp)
		return (NULL);
	while (env_paths[i] != 0)
	{
		full_path = ft_strjoin(env_paths[i], temp);
		if (!full_path)
			return (free(temp), NULL);
		if (access(full_path, F_OK) == 0)
			return (free(temp), full_path);
		free(full_path);
		i++;
	}
	free(full_path);
	return (free(temp), NULL);
}
