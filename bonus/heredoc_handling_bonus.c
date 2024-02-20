/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handling_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lauri <lauri@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:51:31 by lauri             #+#    #+#             */
/*   Updated: 2024/02/20 14:11:25 by lauri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"

void handle_heredoc(t_pipex *cont, char **av)
{
	int	fd;
	char *buffer;

	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		perror("here_doc");
	while (1)
	{
		ft_printf("heredoc> ");
		buffer = get_next_line(fd);
		if (buffer == NULL)
			exit (EXIT_FAILURE);
		if (ft_strncmp(av[3], buffer, ft_strlen(buffer) == 0))
			break ;
		ft_putstr_fd(buffer, fd);
		ft_putchar_fd('\n', fd);
		free(buffer);
	}
	free(buffer);
	close (fd);
	cont->fd_in = open (".heredoc", O_RDONLY);
	if (cont->fd_in < 0)
	{
		unlink(".heredoc");
		perror("heredoc");
	}
}
