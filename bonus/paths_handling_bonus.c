/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_handling_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:58:41 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/29 09:28:16 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"

char	**parse_path(char **envp);
char	*find_path(char *cmd, char **env_paths);

char	**get_paths(char ***cmds, int cmd_count, char **envp)
{
	int		i;
	char	**env_paths;
	char	**paths;

	i = 0;
	env_paths = parse_path(envp);
	paths = (char **) malloc ((cmd_count + 1) * sizeof(char **));
	while (i < cmd_count)
	{
		if (env_paths != NULL)
		{
			paths[i] = find_path(cmds[i][0], env_paths);
		}
		else
			paths[i] = ft_strdup(cmds[i][0]);
		i++;
	}
	paths[i] = 0;
	if (env_paths != NULL)
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
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == NULL)
	{
		i++;
	}
	if (envp[i] == NULL)
		return (NULL);
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
	if (access(cmd, F_OK) == 0)
	{
		full_path = ft_strdup(cmd);
		return (full_path);
	}
	temp = ft_strjoin("/", cmd);
	if (!temp)
		return (NULL);
	while (env_paths[i])
	{
		full_path = ft_strjoin(env_paths[i], temp);
		if (!full_path)
			return (free(temp), NULL);
		if (access(full_path, F_OK) == 0)
			return (free(temp), full_path);
		free(full_path);
		i++;
	}
	free(temp);
	return (NULL);
}
