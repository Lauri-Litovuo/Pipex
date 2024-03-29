/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:58:46 by llitovuo          #+#    #+#             */
/*   Updated: 2024/03/04 10:25:45 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"

static void	init_cont(t_pipex *cont);
int			handle_processes(t_pipex *cont, char **av);
int			wait_children(pid_t *pids, t_pipex *cont);

int	main(int ac, char **av, char **envp)
{
	t_pipex			*cont;
	int				exitcode;

	exitcode = 0;
	if (ac < 5 || \
	(ft_strncmp(av[1], "here_doc", ft_strlen(av[1]) == 0 && ac < 6)))
	{
		write (2, "Invalid arguments.\n", 19);
		return (1);
	}
	cont = (t_pipex *) malloc (sizeof(*cont));
	if (!cont)
		exit (EXIT_FAILURE);
	init_cont(cont);
	if (ft_strncmp(av[1], "here_doc", ft_strlen(av[1])) == 0)
		cont->here_doc = 1;
	cont->cmd_count = count_cmds(ac, av);
	cont->cmds = get_cmds(av, cont->cmd_count);
	cont->paths = get_paths(cont->cmds, cont->cmd_count, envp);
	exitcode = handle_processes(cont, av);
	free_struct(cont);
	return (exitcode);
}

static void	init_cont(t_pipex *cont)
{
	cont->fd_in = -7;
	cont->fd_out = -5;
	cont->paths = NULL;
	cont->cmds = NULL;
	cont->cmd_count = 0;
	cont->errcode = 0;
	cont->here_doc = 0;
}

int	handle_processes(t_pipex *cont, char **av)
{
	pid_t	*pids;
	int		exitcode;

	exitcode = 0;
	pids = ft_calloc((cont->cmd_count + 1), sizeof(int));
	if (pids == 0)
		return (1);
	piping(cont, &pids, av);
	exitcode = wait_children(pids, cont);
	free(pids);
	if (cont->errcode != 0)
		exitcode = cont->errcode;
	if (access(av[4], W_OK) != 0)
	{
		cont->errcode = 1;
		exitcode = 1;
	}
	return (exitcode);
}

int	wait_children(pid_t *pids, t_pipex *cont)
{
	int	exitstatus;
	int	i;
	int	exitcode;

	i = 0;
	exitcode = 0;
	exitstatus = 0;
	while (pids[i] != 0)
	{
		waitpid(pids[i], &exitstatus, 0);
		if (exitstatus == 256 && pids[i] != 0 && \
		cont->cmds[i][0] && ft_strncmp(cont->cmds[i][0], "./", 2) == 0)
			cont->errcode = 126;
		else if (access(cont->paths[i], F_OK) == 0 && exitstatus == 256)
			cont->errcode = 1;
		else if (exitstatus == 256 && pids[i] != 0)
			cont->errcode = 127;
		else
			cont->errcode = WEXITSTATUS(exitstatus);
		i++;
	}
	exitcode = WEXITSTATUS(exitstatus);
	return (exitcode);
}
