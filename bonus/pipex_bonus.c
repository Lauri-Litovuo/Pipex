/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:58:46 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/26 11:45:07 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex_bonus.h"

static void	init_cont(t_pipex *cont);
int			handle_processes(t_pipex *cont, char **av);

int	main(int ac, char **av, char **envp)
{
	t_pipex		*cont;
	int			exitcode;

	if (ac < 5 || (ft_strnstr(av[1], "here_doc", 8) != 0 && ac < 6))
	{
		write (2, "Invalid arguments.\n", 19);
		return (1);
	}
	cont = (t_pipex *) malloc (sizeof(*cont));
	if (!cont)
		return (1);
	init_cont(cont);
	if ((ft_strnstr(av[1], "here_doc", ft_strlen(av[1])) != 0))
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
	cont->fd_in = -1;
	cont->fd_out = -1;
	cont->paths = NULL;
	cont->cmds = NULL;
	cont->cmd_count = 0;
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
	if (piping(cont, &pids, av) != 0)
	{
		exitcode = wait_children(pids);
		free (pids);
		if (access(av[4], X_OK == -1))
		{
			return (127);
		}
		return (exitcode);
	}
	exitcode = wait_children(pids);
	free(pids);
	return (exitcode);
}

int	wait_children(pid_t *pids)
{
	int	exitstatus;
	int	i;
	int	exitcode;

	i = 0;
	while (pids[i] != 0)
	{
		waitpid(pids[i], &exitstatus, 0);
		i++;
	}
	exitcode = WEXITSTATUS(exitstatus);
	return (exitcode);
}
