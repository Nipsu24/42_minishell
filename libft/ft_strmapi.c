/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:33:23 by mmeier            #+#    #+#             */
/*   Updated: 2023/12/11 10:19:41 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ptr;
	unsigned int	len;

	if (!s)
		return (0);
	len = ft_strlen(s);
	i = 0;
	ptr = (char *) malloc ((len + 1) * sizeof(char));
	if (ptr == 0)
		return (NULL);
	if (s && f)
	{
		while (s[i])
		{
			ptr[i] = f(i, s[i]);
			i++;
		}
	}
	ptr[i] = '\0';
	return (ptr);
}
