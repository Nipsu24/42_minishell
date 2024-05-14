/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:22:50 by mmeier            #+#    #+#             */
/*   Updated: 2024/03/14 11:16:03 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_count(int n, int *cmp)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count += ft_putstr_count("-2147483648", cmp);
		return (count);
	}
	else
	{
		if (n < 0)
		{
			count += ft_putchar_count('-', cmp);
			n *= -1;
		}
		if (n >= 10)
		{
			count += ft_putnbr_count((n / 10), cmp);
			count += ft_putnbr_count((n % 10), cmp);
		}
		else
			count += ft_putchar_count((n + '0'), cmp);
	}
	return (count);
}
