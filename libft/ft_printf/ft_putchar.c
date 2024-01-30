/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:21:36 by llitovuo          #+#    #+#             */
/*   Updated: 2023/12/27 16:29:16 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
/**
 * @brief Modified ft_putchar with int parameter to follow how many 
 * characters are written. Returns the incremented lenght.
 * 
 * @param c character to be written
 * @param wlen int lenght that is incremented
 * @return int incremented ++len; returns -1 if fails.
 */

int	ft_putchar(char c, int wlen)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	wlen++;
	return (wlen);
}
