/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 11:13:48 by mmeier            #+#    #+#             */
/*   Updated: 2023/11/06 16:23:48 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1ptr;
	const unsigned char	*s2ptr;
	size_t				i;

	s1ptr = s1;
	s2ptr = s2;
	i = 0;
	while (i < n)
	{
		if (s1ptr[i] > s2ptr[i])
		{
			return (s1ptr[i] - s2ptr[i]);
		}
		else if (s1ptr[i] < s2ptr[i])
		{
			return (s1ptr[i] - s2ptr[i]);
		}
		i++;
	}
	return (0);
}
