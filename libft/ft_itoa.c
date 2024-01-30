/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:13:33 by llitovuo          #+#    #+#             */
/*   Updated: 2023/11/14 12:12:03 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_intlen(int nb)
{
	int	ln;

	ln = 1;
	while (nb > 9 || nb < -9)
	{
		nb /= 10;
		ln++;
	}
	return (ln);
}

static char	ft_get_digit(int nbr)
{
	char	digit;

	if (nbr >= 9)
		nbr %= 10;
	digit = nbr + 48;
	return (digit);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		minus;

	minus = 0;
	len = ft_intlen(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
		minus = 1;
	str = (char *)malloc((len + minus + 1) * sizeof(char));
	if (!(str))
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	str[len + minus] = '\0';
	while (len-- > 0)
	{
		str[(len + minus)] = ft_get_digit(n);
		n /= 10;
	}
	return (str);
}
