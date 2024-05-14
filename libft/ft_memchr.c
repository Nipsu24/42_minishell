/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:02:32 by mmeier            #+#    #+#             */
/*   Updated: 2023/11/06 16:10:52 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*sptr;
	unsigned char		cconvert;
	size_t				i;

	i = 0;
	cconvert = c;
	sptr = s;
	while (n > i)
	{
		if (sptr[i] == cconvert)
			return ((unsigned char *)(sptr + i));
		i++;
	}
	return (NULL);
}
