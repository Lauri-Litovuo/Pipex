/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:23:45 by llitovuo          #+#    #+#             */
/*   Updated: 2023/11/02 11:57:04 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		len;

	len = ft_strlen((char *)s);
	dest = (char *)malloc (len * sizeof(char) + 1);
	if (!(dest))
		return (NULL);
	ft_strlcpy(dest, s, (len + 1));
	return (dest);
}
