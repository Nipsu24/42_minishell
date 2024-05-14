/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexconvert_upper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:46:14 by mmeier            #+#    #+#             */
/*   Updated: 2024/03/14 11:15:47 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_hexconvert_upper(unsigned int n, int *cmp)
{
	int	count;

	count = 0;
	if (n >= 16)
	{
		count += ft_hexconvert_upper((n / 16), cmp);
		n = n % 16;
	}
	if (n >= 10)
	{
		count += ft_putchar_count('A' + (n - 10), cmp);
	}
	else
	{
		count += ft_putchar_count(('0' + n), cmp);
	}
	return (count);
}
