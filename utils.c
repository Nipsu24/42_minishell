/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:20:54 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/16 16:42:49 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include "./libft/libft.h"

/*Counts words (and strings in quotes as one single word)*/
static int	ft_wcount(char const *s, char c, char str_flag)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
			{
				if (s[i] == str_flag && s[i + 1] && i++)
				{
					while (s[i] && s[i] != str_flag)
						i++;
				}
				if (s[i])
					i++;
			}
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

static char	**ft_free(char **arr, size_t j)
{
	while (j > 0)
	{
		free(arr[j - 1]);
		j--;
	}
	free(arr);
	arr = NULL;
	return (NULL);
}

static char	**ft_store_words(char const *s, char c, char **arr, char str_flag)
{
	size_t	start;
	size_t	i;
	size_t	j;
	size_t	q_flag;

	i = 0;
	j = 0;
	start = 0;
	q_flag = 0;
	while (s[i] != 0)
	{
		if (s[i] == str_flag)
			q_flag = 1;
		if (q_flag == 1)
		{
			if (s[i] != 0 && s[i] != c)
			{
				start = i;
				while (s[i] != 0 && s[i] != str_flag)
					i++;
				q_flag = 0;
				arr[j] = ft_substr(s, start, (i - start));
				if (arr[j] == 0)
					return (ft_free(arr, j));
				j++;
			}
		}
		else if (q_flag == 0)
		{
			if (s[i] != 0 && s[i] != c)
			{
				start = i;
				while (s[i] != 0 && s[i] != c)
					i++;
				arr[j] = ft_substr(s, start, (i - start));
				if (arr[j] == 0)
					return (ft_free(arr, j));
				j++;
			}
			else
				i++;
		}
	}
	arr[j] = 0;
	return (arr);
}

char	**ft_tokenize(char const *s, char c, char str_flag)
{
	char	**strings;

	if (!s)
		return (0);
	strings = malloc (sizeof(char *) * (ft_wcount(s, c, str_flag) + 1));
	if (strings == 0 || s == 0)
		return (NULL);
	return (ft_store_words(s, c, strings, str_flag));
}

int	main(int ac, char *av[])
{
	
	// int nbr;
	// nbr = ft_wcount(av[1], ' ', '"');
	// ft_printf("%d\n", nbr);
	char **string;
	int	i;

	i = 0;
	if (ac > 1)
	{
		string = ft_tokenize(av[1], ' ', '"');
		while (string[i])
		{
			ft_printf("%s\n", string[i]);
			i++;
		}
	}
	return (0);
}