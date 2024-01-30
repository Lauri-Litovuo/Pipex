/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:14:15 by llitovuo          #+#    #+#             */
/*   Updated: 2023/11/14 12:11:18 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*sp;
	char	ch;
	char	*temp;
	int		i;

	sp = (char *)s;
	ch = c;
	i = 0;
	while (*sp != '\0')
	{
		if (*sp == ch)
		{
			temp = sp;
			i++;
		}
		sp++;
	}
	if (*sp == ch)
		return (sp);
	else if (i >= 1)
		return (temp);
	else
		return (NULL);
}
