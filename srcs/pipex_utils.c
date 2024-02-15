/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:28:11 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/15 11:25:48 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

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

int	get_fds(t_pipex *cont, char **av)
{
	cont->fd_in = open(av[1], O_RDONLY);
	cont->fd_out = open(av[cont->cmd_count + 2], \
	O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (cont->fd_out == -1 || cont->fd_in == -1)
	{
		if (cont->fd_in == -1)
		{
			if (cont->fd_out != -1)
				close(cont->fd_out);
			perror (av[1]);
			free_struct(cont);
			return (0);
		}
		perror("pipex");
		if (cont->fd_in != -1)
			close(cont->fd_in);
		free_struct(cont);
		return (-1);
	}
	return (1);
}
