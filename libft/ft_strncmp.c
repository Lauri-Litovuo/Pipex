/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:30:05 by llitovuo          #+#    #+#             */
/*   Updated: 2023/11/11 13:48:35 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				diff;
	unsigned char	*sp1;
	unsigned char	*sp2;

	sp1 = (unsigned char *)s1;
	sp2 = (unsigned char *)s2;
	diff = 0;
	if (n == 0)
		return (0);
	while (n > 0 && *sp1 != '\0')
	{
		if (*sp1 == *sp2)
		{
			diff = (*s1 - *s2);
			sp1++;
			sp2++;
			n--;
		}
		else
			return (*sp1 - *sp2);
	}
	if (n == 0)
		return (diff);
	return (*sp1 - *sp2);
}
