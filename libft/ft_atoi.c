/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:10:53 by llitovuo          #+#    #+#             */
/*   Updated: 2023/11/14 17:07:02 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	skip_signs(const char *str, int i)
{
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
	}
	return (i);
}

static int	ft_isneg(const char *str, int i)
{
	if (str[i] == '-')
		return (-1);
	else
		return (1);
}

int	ft_atoi(const char *str)
{
	long int	result;
	int			negative;
	int			i;

	result = 0;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	negative = ft_isneg(str, i);
	i = skip_signs(str, i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result >= (LONG_MAX / 10) && \
				(result > LONG_MAX / 10 || str[i] - '0' > LONG_MAX % 10))
		{
			if (negative == 1)
				return (-1);
			else
				return (0);
		}
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (negative * (int)result);
}
