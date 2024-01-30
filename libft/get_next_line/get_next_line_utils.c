/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 09:14:30 by llitovuo          #+#    #+#             */
/*   Updated: 2023/12/27 16:59:10 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlen_gnl(char *a)
{
	int	i;

	i = 0;
	while (a[i] != 0)
	{
		i++;
	}
	return (i);
}

char	*ft_strchr_gnl(char *s, int c)
{
	char	*sp;
	char	ch;

	if (!s)
		return (NULL);
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

size_t	ft_strlcpy_gnl(char *dst, char *src, size_t dstsize)
{
	unsigned int	i;
	char			*cpysrc;

	cpysrc = (char *)src;
	i = 0;
	if (dstsize > 0)
	{
		while (cpysrc[i] != '\0' && i + 1 < dstsize)
		{
			dst[i] = cpysrc[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (cpysrc[i] != '\0')
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcat_gnl(char *dst, char *src, size_t dstsize)
{
	unsigned int	dst_len;
	unsigned int	src_len;
	unsigned int	temp;
	unsigned int	i;

	if ((dst == NULL || *dst == '\0') && src && dstsize == 0)
		return (ft_strlen_gnl(src));
	i = 0;
	dst_len = ft_strlen_gnl(dst);
	src_len = ft_strlen_gnl(src);
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

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*joint;
	int		len;

	if (!s1 && s2)
	{
		s1 = (char *) malloc (1 * sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	len = ft_strlen_gnl(s1);
	if (!s2)
	{
		free (s1);
		return (NULL);
	}
	len += ft_strlen_gnl(s2);
	joint = (char *) malloc((len + 1) * sizeof(char));
	if (!joint)
		return (free (s1), NULL);
	ft_strlcpy_gnl(joint, s1, len + 1);
	free (s1);
	ft_strlcat_gnl(joint, s2, len + 1);
	return (joint);
}
