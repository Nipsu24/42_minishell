/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer_a.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:20:54 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/26 15:24:26 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Counts words (and strings in quotes as one single word)*/
static int	ft_wcount(char *s)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (s[i] == '\0')
		count++;
	else
	{
		while (s[i])
		{
			if (s[i] && s[i] != ' ')
			{
				count++;
				while (s[i] && s[i] != ' ')
				{
					if ((is_quote(s[i]) && s[i + 1]))
						w_count_quote_iter(s, &i);
					if (s[i])
						i++;
				}
			}
			while (s[i] && s[i] == ' ')
				i++;
		}
	}
	return (count);
}

/*Helper function of ft_store_words. Iterates through quoted passages and copies
  those into array of strings*/
static char	**ft_iter_quote(char *s, size_t *i, size_t *j, char **arr)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (!is_quote(s[*i]) && s[*i])
		(*i)++;
	arr[*j] = ft_substr(s, start, (*i - start + 1));
	if (arr[*j] == 0)
		return (free_arr_rev(&arr, *j));
	(*j)++;
	if (s[*i])
		(*i)++;
	return (arr);
}

/*Helper function of ft_store_words. Iterates through unquoted parts and copies
  those into array of strings*/
static char	**ft_iter_str(char *s, size_t *i, size_t *j, char **arr)
{
	size_t	start;
	char	c;

	start = *i;
	c = ' ';
	while (s[*i] != c && s[*i])
		(*i)++;
	if (s[*i] == c)
	{
		while (between_quotes(s, *i))
			(*i)++;
	}
	if (is_quote(s[*i]))
		(*i)++;
	arr[*j] = ft_substr(s, start, (*i - start));
	if (arr[*j] == 0)
		return (free_arr_rev(&arr, *j));
	(*j)++;
	return (arr);
}

/*Iterates through string and copies identified passages (words delimited 
  by ' ' and passages enclosed by quotes) into array of strings*/
static char	**ft_store_words(char *s, char **arr)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s[i] == '\0')
	{
		arr[j] = ft_strdup("");
		arr[j + 1] = 0;
		return (arr);
	}
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			if (!ft_iter_quote(s, &i, &j, arr))
				return (free_arr_rev(&arr, j));
		}
		if (s[i] && s[i] != ' ' && !is_quote(s[i]))
		{
			if (!ft_iter_str(s, &i, &j, arr))
				return (free_arr_rev(&arr, j));
		}
		else if (s[i] && !is_quote(s[i]))
			i++;
	}
	arr[j] = 0;
	j = 0;
	return (arr);
}

/*Modification of ft_split. Splits input into array of strings and
  treats quoted passages as single string*/
char	**ft_tokenize(char *s)
{
	char	**arr;

	if (!s)
		return (0);
	arr = (char **) malloc (sizeof(char *) * (ft_wcount(s) + 1));
	if (arr == 0 || s == 0)
		return (NULL);
	return (ft_store_words(s, arr));
}
