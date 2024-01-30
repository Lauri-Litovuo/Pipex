/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:42:59 by llitovuo          #+#    #+#             */
/*   Updated: 2023/11/14 09:53:16 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_retzero(void)
{
	char	*empty;

	empty = (char *) malloc(1 * sizeof(char));
	if (!(empty))
		return (NULL);
	*empty = '\0';
	return (empty);
}

char	*ft_substr(char const *s, unsigned int start, size_t ln)
{
	char	*dest;

	if (s == 0)
		return (0);
	else if (ln == 0 || start >= ft_strlen(s))
		return (ft_retzero());
	else if (ln <= ft_strlen(s) - start)
		dest = (char *) malloc(ln * sizeof(char) + 1);
	else
		dest = (char *) malloc((ft_strlen(s) - start) * sizeof(char) + 1);
	if (!(dest))
		return (NULL);
	if (ln < ft_strlen(s))
		ft_strlcpy(dest, s + start, ((size_t)ln + 1));
	else
		ft_strlcpy(dest, s + start, ft_strlen(s) - start + 1);
	return (dest);
}
