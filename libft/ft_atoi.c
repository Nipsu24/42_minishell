/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:20:12 by mmeier            #+#    #+#             */
/*   Updated: 2023/11/15 16:46:37 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_convertno(const char *str, int n, int minus)
{
	long int	number;
	long int	prenbr;

	prenbr = 0;
	number = 0;
	while (str[n] >= 48 && str[n] <= 57)
	{
		number *= 10;
		number += str[n] - 48;
		n++;
		if (prenbr > number)
		{
			if (minus > 0)
				return (0);
			else
				return (-1);
		}
		prenbr = number;
	}
	return (number);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	number;
	int	plus;

	minus = 0;
	plus = 0;
	number = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus++;
		if (str[i] == '+')
			plus++;
		if (minus + plus > 1)
			return (0);
		i++;
	}
	number = ft_convertno(str, i, minus);
	if (minus == 1)
		return (-number);
	return (number);
}
