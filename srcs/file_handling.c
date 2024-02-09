/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:59:09 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/09 14:37:25 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

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


