/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:41:47 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/28 14:04:50 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

static void	init_cont(t_pipex *cont);
int			handle_processes(t_pipex *cont, char **av);

int	main(int ac, char **av, char **envp)
{
	t_pipex			*cont;
	int				exitcode;

	exitcode = 0;
	if (ac != 5)
	{
		write (2, "Argument count is not five.\n", 28);
		return (1);
	}
	cont = (t_pipex *) malloc (sizeof(*cont));
	if (!cont)
		exit (EXIT_FAILURE);
	init_cont(cont);
	cont->cmd_count = count_cmds(ac);
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
}

int	handle_processes(t_pipex *cont, char **av)
{
	pid_t	*pids;
	int		exitcode;

	exitcode = 0;
	pids = ft_calloc((cont->cmd_count + 1), sizeof(int));
	if (pids == 0)
		return (1);
	if (piping(cont, &pids, av) != 0)
	{
		exitcode = wait_children(pids, cont);
		free (pids);
		if (cont->errcode != 0)
			exitcode = cont->errcode;
		return (exitcode);
	}
	exitcode = wait_children(pids, cont);
	free(pids);
	if (cont->errcode != 0)
		exitcode = cont->errcode;
	return (exitcode);
}

int	wait_children(pid_t *pids, t_pipex *cont)
{
	int	exitstatus;
	int	i;
	int	exitcode;

	i = 0;
	while (pids[i] != 0)
	{
		waitpid(pids[i], &exitstatus, 0);
		if (exitstatus == 256 && pids[i] != 0 && \
		ft_strnstr(cont->cmds[i][0], "./", 2) != NULL)
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
