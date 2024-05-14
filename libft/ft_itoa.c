/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:13:42 by mmeier            #+#    #+#             */
/*   Updated: 2023/11/15 16:48:10 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ncount(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n && ++count)
		n = n / 10;
	return (count);
}

char	*ft_itoa(int n)
{
	char		*ptr;
	long int	count;
	long int	i;
	long int	numb;

	count = ft_ncount(n);
	numb = (long int)n;
	i = 0;
	ptr = (char *) malloc ((count + 1) * sizeof(char));
	if (ptr == 0)
		return (NULL);
	ptr[count] = '\0';
	if (numb < 0)
	{
		ptr[0] = '-';
		numb *= -1;
		i = 1;
	}
	while (count > i)
	{
		count--;
		ptr[count] = (numb % 10) + '0';
		numb = numb / 10;
	}
	return (ptr);
}
