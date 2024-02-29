/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:10:52 by llitovuo          #+#    #+#             */
/*   Updated: 2024/02/29 12:47:46 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_count_strs(char *str, char ch)
{
	int	count;

	count = 0;
	while (*str != '\0')
	{
		if (*str == ch)
			str++;
		else
		{
			while (*str != ch && *str != '\0')
			{
				str++;
			}
			count++;
		}
	}
	return (count);
}

static void	free_array(char **array, int size)
{
	while (size >= 0)
	{
		free(array[size]);
		size--;
	}
	free(array);
}

static int	put_substrs(char const *str, char **arr, char ch, int k)
{
	size_t			i;
	unsigned int	starts;

	i = 0;
	starts = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ch)
			i++;
		else
		{
			starts = i;
			while (str[i] != ch && str[i] != '\0')
				i++;
			arr[k] = ft_substr((const char *)str, starts, (i - starts));
			if (arr[k] == NULL)
			{
				free_array(arr, k);
				return (0);
			}
			k++;
		}
	}
	arr[k] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**str_arr;
	int		n;
	int		k;

	k = 0;
	if (!(s))
		return (NULL);
	n = ft_count_strs((char *)s, c);
	str_arr = (char **) malloc((n + 1) * sizeof(char **));
	if (! (str_arr))
		return (NULL);
	if (put_substrs(s, str_arr, c, k) == 0)
		return (NULL);
	return (str_arr);
}
