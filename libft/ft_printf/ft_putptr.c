/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:59:22 by llitovuo          #+#    #+#             */
/*   Updated: 2023/12/27 16:50:41 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putptr(unsigned long long nbr, int *wlen, int base, char *b_symb)
{
	if (*wlen == 0)
	{
		if (ft_putstr("0x", 0) < 0)
			return (-1);
		*wlen += 2;
	}
	if (nbr == 0)
	{
		if (ft_putchar('0', 0) < 0)
			return (-1);
		return (1);
	}
	if (nbr >= (unsigned long long) base)
		*wlen += ft_putptr(nbr / base, wlen, base, b_symb);
	if (ft_putchar(b_symb[nbr % base], 0) < 0)
		return (-1);
	return (1);
}
