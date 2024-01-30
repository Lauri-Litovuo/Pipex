/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:41:47 by llitovuo          #+#    #+#             */
/*   Updated: 2024/01/30 17:13:04 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"
/**
 * @brief 
 * 
 * @param ac 
 * @param av These should be:
 * 				av[0] = pipex.c, 
 *				av[1] = file1, 
 * 				av[2] = cmd1, 
 * 				av[3] = cmd2, 
 * 				av[4] = file2
 * 
 * @return int 
 */

check_input_validity(int ac, char **av);

int	main(int ac, char **av)
{
	int		fd_f1;
	int		fd_f2;

	check_input_validity (ac, av);

	fd_f1 = open (av[1], O_RDONLY);
	fd_f2 = open (av[4], O_WRONLY);
}

check_input_validity(int ac, char **av)
{
	if (ac != 5)
	{
		write (2, "Too few arguments.\n", 19);
		return (-1);
	}
	if (access (av[1], F_OK) && access(av[4], F_OK))
		perror ("File not found: ");
	if (access(av[1], R_OK) == -1)
		perror ("Error in file: ");
	if (access(av[4], W_OK) == -1)
		perror ("Error in file: ");
	if ()
}
