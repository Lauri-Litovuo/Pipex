#include <stdio.h>
#include "../libft/libft.h"
#include "../incl/pipex.h"

void	init_cont(t_pipex *cont)
{
	cont->fd_in = -1;
	cont->fd_out = -1;
	cont->paths = NULL;
	cont->cmds = NULL;
	cont->cmd_count = 0;
	cont->here_doc = 0; // for bonus
}

int	main(int ac, char **av, char **envp)
{
	t_pipex		*cont;
	int			i;
	int			j;

	i = 0;
	j = 0;
	cont = (t_pipex *) malloc (sizeof(*cont));
	if (!cont)
		exit(1);
	init_cont(cont);
	cont->cmd_count = count_cmds(ac, av);
	cont->cmds = get_cmds(av, cont->cmd_count);
	printf("Command count is %d and commands are:\n", cont->cmd_count);
	while (cont->cmds[i] != NULL)
	{
		while (cont->cmds[i][j] != NULL)
		{
			printf("'%s' ", cont->cmds[i][j]);
			j++;
		}
		printf("\n");
		i++;
		j = 0;
	}
	cont->paths = get_paths(cont->cmds, cont->cmd_count, envp);
	i = 0;
	while (cont->paths[i] != NULL)
	{
		printf("'%s' ", cont->paths[i]);
		i++;
	}
	if (get_fds(cont, av) == -1)
		return (1);
	printf("\nfd_in: %d\nfd_out: %d\n", cont->fd_in, cont->fd_out);
	close(cont->fd_in);
	close(cont->fd_out);
	free_struct(cont);
	return (0);
}
