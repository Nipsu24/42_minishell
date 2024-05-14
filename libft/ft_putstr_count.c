/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:20:47 by mmeier            #+#    #+#             */
/*   Updated: 2024/03/14 11:16:18 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_count(char *s, int *cmp)
{
	int	count;

	count = 0;
	if (s == NULL)
		return (ft_putstr_count("(null)", cmp));
	while (*s != '\0')
	{
		count += ft_putchar_count(*s, cmp);
		s++;
	}
	return (count);
}
