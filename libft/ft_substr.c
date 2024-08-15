/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:58:44 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/15 16:19:31 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s)
		return (0);
	if (start + len > (ft_strlen(s)))
		len = (ft_strlen(s) - start);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	ptr = (char *) malloc ((len + 1) * sizeof(char));
	if (ptr == 0)
		return (NULL);
	if (len == 0)
		ptr[len] = '\0';
	while (len > 0)
	{
		ptr[i] = s[start];
		len--;
		start++;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
