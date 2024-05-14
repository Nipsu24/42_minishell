/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:27:48 by mmeier            #+#    #+#             */
/*   Updated: 2024/03/14 11:16:12 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(void *s, int *cmp)
{
	int					count;
	unsigned long long	i;

	i = (unsigned long long) s;
	count = 0;
	count += ft_putstr_count("0x", cmp);
	count += ft_hexconvert_lower(i, cmp);
	return (count);
}
