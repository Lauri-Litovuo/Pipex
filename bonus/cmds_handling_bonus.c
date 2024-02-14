/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handling_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:58:30 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/14 14:59:35 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

int	count_cmds(int ac, char **av)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if(ft_strnstr(av[1], "here_doc", 8) != 0)
		i = 4;
	else
		i = 3;
	count = ac - i;
	return (count);
}

char	***get_cmds(char **av, int cmd_count)
{
	char	***cmds;
	int		i;
	int		j;

	i = 0;
	j = 2;
	if (ft_strnstr(av[1], "here_doc", 8) != 0)
		j = 3;
	cmds = (char ***) malloc((cmd_count + 1) * sizeof(char ***));
	if (!cmds)
		return (NULL);
	while (i < cmd_count)
	{
		cmds[i] = ft_split(av[i + j], ' ');
		if (cmds[i] == NULL)
		{
			return (0);
		}
		i++;
	}
	cmds[i] = NULL;
	return (cmds);
}
