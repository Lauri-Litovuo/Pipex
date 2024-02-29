/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 12:03:07 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/29 12:51:13 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

int	count_cmds(int ac)
{
	int	i;
	int	count;

	count = 0;
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
