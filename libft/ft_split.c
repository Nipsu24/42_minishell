/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 09:21:38 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/05 15:30:07 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_subcount(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != 0)
	{
		if (s[i] != 0 && s[i] != c)
		{
			count++;
			while (s[i] != 0 && s[i] != c)
				i++;
		}
		while (s[i] != 0 && s[i] == c)
			i++;
	}
	return (count);
}

static char	**ft_free_split(char **result, size_t j)
{
	while (j > 0)
	{
		free(result[j - 1]);
		j--;
	}
	free(result);
	result = NULL;
	return (NULL);
}

static char	**ft_writewords(char const *s, char c, char **strings)
{
	size_t	start;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	start = 0;
	while (s[i] != 0)
	{
		if (s[i] != 0 && s[i] != c)
		{
			start = i;
			while (s[i] != 0 && s[i] != c)
				i++;
			strings[j] = ft_substr(s, start, (i - start));
			if (strings[j] == 0)
				return (ft_free_split(strings, j));
			j++;
		}
		else
			i++;
	}
	strings[j] = 0;
	return (strings);
}

char	**ft_split(char const *s, char c)
{
	char	**strings;

	if (!s)
		return (0);
	strings = (char **) malloc (sizeof(char *) * (ft_subcount(s, c) + 1));
	if (strings == 0 || s == 0)
		return (NULL);
	return (ft_writewords(s, c, strings));
}
