/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:22:38 by mmeier            #+#    #+#             */
/*   Updated: 2024/04/08 10:24:17 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	product;

	product = size * count;
	if (size == 0 || count == 0)
	{
		ptr = malloc(0);
		return (ptr);
	}
	if (product % count != 0 || product % size != 0)
		return (NULL);
	ptr = (char *) malloc (count * size);
	if (ptr == 0)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
