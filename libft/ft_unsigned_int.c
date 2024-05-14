/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_int.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:46:08 by mmeier            #+#    #+#             */
/*   Updated: 2024/03/14 11:16:27 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_unsigned_int_count(unsigned int n, int *cmp)
{
	int	count;

	count = 0;
	if (n >= 10)
	{
		count += ft_unsigned_int_count((n / 10), cmp);
		count += ft_unsigned_int_count((n % 10), cmp);
	}
	else
	{
		count += ft_putchar_count((n + '0'), cmp);
	}
	return (count);
}
