/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 11:55:15 by llitovuo          #+#    #+#             */
/*   Updated: 2023/11/14 09:09:29 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_emptystr(void)
{
	char	*empty;

	empty = (char *) malloc(1 * sizeof(char));
	if (!(empty))
		return (NULL);
	*empty = '\0';
	return (empty);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		i;
	int		first;
	int		last;

	i = 0;
	first = 0;
	if (*s1 == 0 || s1[i] == '\0')
		return (ft_emptystr());
	last = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[i]) != 0 && i < last - 1)
	{
		first = i;
		i++;
	}
	i = last;
	while (ft_strchr(set, s1[i]) != NULL && i >= first)
	{
		last = i;
		i--;
	}
	if (first != last && ft_strchr(set, s1[0]) != 0)
		first += 1;
	trim = ft_substr(s1, first, (last - first));
	return (trim);
}
