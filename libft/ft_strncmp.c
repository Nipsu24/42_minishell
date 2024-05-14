/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:16:45 by mmeier            #+#    #+#             */
/*   Updated: 2023/11/06 17:10:35 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*u1;
	unsigned char	*u2;

	u1 = (unsigned char *)(s1);
	u2 = (unsigned char *)(s2);
	i = 0;
	while ((u1[i] != '\0' || u2[i] != '\0') && i < n)
	{
		if (u1[i] > u2[i])
		{
			return (u1[i] - u2[i]);
		}
		else if (u1[i] < u2[i])
		{
			return (u1[i] - u2[i]);
		}
		i++;
	}
	return (0);
}
