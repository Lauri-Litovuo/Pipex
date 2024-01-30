/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 12:23:33 by llitovuo          #+#    #+#             */
/*   Updated: 2023/10/30 10:40:51 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

void	*ft_memset(void *ptr, int c, size_t len)
{
	unsigned char	b;
	unsigned char	*ucptr;

	b = c;
	ucptr = ptr;
	while (len > 0)
	{
		*ucptr = c;
		ucptr++;
		len--;
	}
	return (ptr);
}
