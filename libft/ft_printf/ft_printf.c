/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 11:54:24 by llitovuo          #+#    #+#             */
/*   Updated: 2023/12/27 16:28:56 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/**
 * @brief The fuction is designed to test the success of write function
 * 
 * @param len initial lenght of the string.
 * @param wlen written lenght.
 * @return int returns len + written lenght OR -1 if either has failed.
 */

static int	fail_check(int len, int wlen)
{
	if (wlen < 0 || len < 0)
		return (-1);
	else
		return (len + wlen);
}

/**
 * @brief The function guides args to right functions based on format specifier.
 * 
 * @param str the string that has the format specifiers.
 * @param args given va_list
 * @return int int returns written lenght
 */

static int	fs_sorter(const char *str, va_list args)
{
	int	wlen;

	wlen = 0;
	if (*str == 'c')
		wlen = ft_putchar(va_arg(args, int), wlen);
	else if (*str == 's')
		wlen = ft_putstr(va_arg(args, char *), wlen);
	else if (*str == 'p')
		wlen += ft_putptr(va_arg(args, unsigned long long), \
		&wlen, 16, "0123456789abcdef");
	else if (*str == 'i' || *str == 'd')
		wlen += ft_putnbr_base(va_arg(args, int), &wlen, 10, "0123456789");
	else if (*str == 'u')
		wlen += ft_putnbr_base(va_arg(args, unsigned int), \
		&wlen, 10, "0123456789");
	else if (*str == 'x')
		wlen += ft_putnbr_base(va_arg(args, unsigned int), \
		&wlen, 16, "0123456789abcdef");
	else if (*str == 'X')
		wlen += ft_putnbr_base(va_arg(args, unsigned int), \
		&wlen, 16, "0123456789ABCDEF");
	else if (*str == '%')
		wlen = ft_putchar('%', wlen);
	return (wlen);
}

/**
 * @brief The function prints cspdiuxX% conversions
 * 
 * @param str printed string with format specifiers
 * @param ... va_listed format specifiers
 * @return int the full lenght of printed string or -1 if failed.
 */

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, str);
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			len = fail_check(len, fs_sorter(str, args));
			str++;
		}
		else
		{
			len = fail_check(len, ft_putchar(*str, 0));
			str++;
		}
		if (len < 0)
			break ;
	}
	va_end(args);
	if (len < 0)
		return (-1);
	return (len);
}
