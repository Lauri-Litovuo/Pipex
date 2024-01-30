/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:54:08 by llitovuo          #+#    #+#             */
/*   Updated: 2023/11/16 10:32:43 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	dst_len;
	unsigned int	src_len;
	unsigned int	temp;
	unsigned int	i;

	if ((dst == NULL || *dst == '\0') && src && dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	temp = 0;
	if (dstsize > 0)
	{
		temp = dst_len;
		while (dst_len < dstsize - 1 && src[i] != '\0')
		{
			dst[dst_len] = src[i];
			dst_len++;
			i++;
		}
		dst[dst_len] = '\0';
	}
	if (dstsize < dst_len)
		return (dstsize + src_len);
	return (temp + src_len);
}
