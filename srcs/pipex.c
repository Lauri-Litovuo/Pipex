/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:41:47 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/09 16:01:45 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

static void	init_cont(t_pipex *cont);

int	main(int ac, char **av, char **envp)
{
	t_pipex		*cont;
	int			exitcode;

	i = 0;
	if (ac != 5) //|| (ft_strnstr(av[1], "here_doc", 8) == 0 && ac < 6)) FOR BONUS
	{
		write (2, "Too few arguments.\n", 19);
		return (-1);
	}
	cont = (t_pipex *) malloc (sizeof(*cont));
	if (!cont)
		return (1);
	init_cont(cont);
	if ((ft_strnstr(av[1], "here_doc", ft_strlen(av[1])) != 0)) //for bonus
		cont->here_doc = 1;
	cont->cmd_count = count_cmds(ac, av);
	cont->cmds = get_cmds(av, cont->cmd_count);
	cont->paths = get_paths(cont->cmds, cont->cmd_count, envp);
	if (get_fds(cont, av) == -1)
		return (1);
	exitcode = handle_processes(cont);
	free_struct(cont);
	return (0);
}

static void	init_cont(t_pipex *cont)
{
	cont->fd_in = -1;
	cont->fd_out = -1;
	cont->paths = NULL;
	cont->cmds = NULL;
	cont->cmd_count = 0;
	cont->here_doc = 0; // for bonus
}






