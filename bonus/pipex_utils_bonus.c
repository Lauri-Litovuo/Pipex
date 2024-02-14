/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:58:51 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/14 14:58:53 by llitovuo         ###   ########.fr       */
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
	// if (cont->here_doc == 1)
	// {
	// 	handle_heredoc(cont, av);
	// }
	cont->fd_in = open(av[1], O_RDONLY);
	if (cont->fd_in == -1)
	{
		perror ("pipex"); //check if a function is needed for these
	}
	cont->fd_out = open(av[cont->cmd_count + 2], O_RDWR | O_TRUNC | O_CREAT, 0644);
	//printf("cont_fd_out opened to %d\n", cont->fd_out);
	if (cont->fd_out == -1)
	{
		perror("pipex");
		if (cont->fd_in != -1)
			close(cont->fd_in);
		free_struct(cont);
		return (-1);
	}
	return (1);
}

