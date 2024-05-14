/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:57:02 by mmeier            #+#    #+#             */
/*   Updated: 2024/03/14 11:15:52 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_convert(va_list args, const char *str, int *cmp)
{
	int	count;

	count = 0;
	if (*str == 'c')
		count += ft_putchar_count(va_arg(args, int), cmp);
	else if (*str == 's')
		count += ft_putstr_count(va_arg(args, char *), cmp);
	else if (*str == 'p')
		count += ft_putptr(va_arg(args, void *), cmp);
	else if (*str == 'd' || *str == 'i')
		count += ft_putnbr_count(va_arg(args, int), cmp);
	else if (*str == 'u')
		count += ft_unsigned_int_count(va_arg(args, unsigned int), cmp);
	else if (*str == 'x')
		count += ft_hexconvert_lower(va_arg(args, unsigned int), cmp);
	else if (*str == 'X')
		count += ft_hexconvert_upper(va_arg(args, unsigned int), cmp);
	else if (*str == '%')
		count += ft_putchar_count('%', cmp);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;
	int		cmp;

	count = 0;
	cmp = 1;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (!*str)
				break ;
			count += ft_convert(args, str, &cmp);
		}
		else
			count += ft_putchar_count(*str, &cmp);
		str++;
	}
	va_end (args);
	if (cmp == -1)
		return (-1);
	return (count);
}
