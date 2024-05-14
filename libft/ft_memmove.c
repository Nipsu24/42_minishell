/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:06:44 by mmeier            #+#    #+#             */
/*   Updated: 2023/11/09 11:03:48 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)

{
	char	*dstptr;
	char	*srcptr;
	size_t	i;

	srcptr = (char *) src;
	dstptr = (char *) dst;
	i = 0;
	if (dstptr > srcptr)
	{
		while (len > 0)
		{
			dstptr[len - 1] = srcptr[len - 1];
			len--;
		}
	}
	else if (dstptr < srcptr)
	{
		while (i < len)
		{
			dstptr[i] = srcptr[i];
			i++;
		}
	}
	return (dst);
}
