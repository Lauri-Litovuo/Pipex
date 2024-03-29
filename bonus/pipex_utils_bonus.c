/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:58:51 by llitovuo          #+#    #+#             */
/*   Updated: 2024/03/01 17:11:35 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"

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

int	get_fdin(t_pipex *cont, char **av)
{
	if (cont->here_doc == 1)
	{
		handle_heredoc(cont, av);
		if (cont->fd_in < 0)
		{
			write (2, "pipex: ", 7);
			perror("heredoc");
			return (-1);
		}
		return (0);
	}
	else
	{
		cont->fd_in = open(av[1], O_RDONLY);
		if (cont->fd_in == -1)
		{
			write (2, "pipex: ", 7);
			perror (av[1]);
			return (-1);
		}
	}
	return (0);
}

int	get_fdout(t_pipex *cont, char **av)
{
	if (cont->here_doc == 1)
		cont->fd_out = open(av[cont->cmd_count + 3], \
		O_RDWR | O_APPEND | O_CREAT, 0644);
	else
		cont->fd_out = open(av[cont->cmd_count + 2], \
		O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (cont->fd_out == -1)
	{
		write (2, "pipex: ", 7);
		if (cont->here_doc == 1)
		{
			perror(av[cont->cmd_count + 3]);
		}
		else
		{
			perror(av[cont->cmd_count + 2]);
		}
		if (cont->fd_in != -1)
			close(cont->fd_in);
		return (-1);
	}
	return (0);
}

void	write_error(char *name, char *errmsg)
{
	write (2, "pipex: ", 7);
	ft_putstr_fd(name, 2);
	write(2, ": ", 2);
	ft_putstr_fd(errmsg, 2);
	write (2, "\n", 1);
}

void	handle_heredoc(t_pipex *cont, char **av)
{
	int		fd;
	char	*buffer;

	fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		perror("here_doc");
	while (1)
	{
		ft_printf("heredoc> ");
		buffer = get_next_line(0);
		if (buffer == NULL)
			exit (EXIT_FAILURE);
		if (ft_strncmp(av[2], buffer, ft_strlen(buffer) - 1) == 0)
			break ;
		ft_putstr_fd(buffer, fd);
		free(buffer);
	}
	free(buffer);
	close (fd);
	cont->fd_in = open (".heredoc", O_RDONLY);
	if (cont->fd_in < 0)
		unlink(".heredoc");
}
