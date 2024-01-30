/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 16:43:03 by llitovuo          #+#    #+#             */
/*   Updated: 2023/11/04 17:31:05 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int				len;
	char			*dest;
	unsigned int	i;
	char			*start;

	len = ft_strlen((char *)s);
	dest = (char *) malloc((len + 1) * sizeof(char));
	if (!(dest))
		return (NULL);
	start = dest;
	i = 0;
	while (*s != '\0')
	{
		*dest = f(i, *s);
		i++;
		s++;
		dest++;
	}
	*dest = '\0';
	return (start);
}
