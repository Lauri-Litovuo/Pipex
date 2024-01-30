/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 08:39:31 by llitovuo          #+#    #+#             */
/*   Updated: 2023/11/14 12:10:41 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr(const char *s, int c)
{
	char	*sp;
	char	ch;

	sp = (char *)s;
	ch = c;
	while (*sp != '\0')
	{
		if (*sp == ch)
			return (sp);
		sp++;
	}
	if (*sp == ch)
		return (sp);
	return (NULL);
}
