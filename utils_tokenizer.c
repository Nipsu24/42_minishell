/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:20:54 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/20 14:45:47 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Helper function of ft_wcount, iterates through quoted part of sting*/
static void	w_count_quote_iter(const char *s, char str_flag, int *i)
{
	(*i)++;
	while (s[*i] && s[*i] != str_flag)
		(*i)++;
}

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
				if (s[i] == str_flag && s[i + 1])
					w_count_quote_iter(s, str_flag, &i);
				if (s[i])
					i++;
			}
		}
		while (s[i] && s[i] == c)
			i++;
	}
	return (count);
}

/*Helper function of ft_store_words. Iterates through quoted passages and copies
  those into strings of array*/
static char	**ft_iter_quote(char const *s, size_t *i, size_t *j, char **arr, char str_flag)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (s[*i] != str_flag && s[*i])
		(*i)++;
	arr[*j] = ft_substr(s, start, (*i - start + 1));
	if (arr[*j] == 0)
		return (ft_free(arr, *j));
	(*j)++;
	if (s[*i])
		(*i)++;
	return (arr);
}

/*Helper function of ft_store_words. Iterates through unquoted parts and copies
  those into array of strings*/
static char	**ft_iter_str(char const *s, size_t *i, size_t *j, char **arr, char c)
{
	size_t	start;

	start = *i;
	while (s[*i] != c && s[*i])
		(*i)++;
	arr[*j] = ft_substr(s, start, (*i - start));
	if (arr[*j] == 0)
		return (ft_free(arr, *j));
	(*j)++;
	return (arr);
}

/*Iterates through string and copies identified passages (words delimited 
  by char c and passages enclosed by str_flag - e.g. '"') into array of 
  strings*/
static char	**ft_store_words(char const *s, char c, char **arr, char str_flag)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == str_flag)
		{
			if (!ft_iter_quote(s, &i, &j, arr, str_flag))
				return (ft_free(arr, j));
		}
		if (s[i] && s[i] != c && s[i] != str_flag)
		{
			if (!ft_iter_str(s, &i, &j, arr, c))
				return (ft_free(arr, j));
		}
		else if (s[i] && s[i] != str_flag)
			i++;
	}
	arr[j] = 0;
	return (arr);
}

/*Modification of ft_split. Takes in addition to delimiter also another 
  argument 'str_flag' which can identify quoted passages within a string
  and treats these passages as 'one word' when populating the array of 
  strings*/
char	**ft_tokenize(char const *s, char c, char str_flag)
{
	char	**arr;

	if (!s)
		return (0);
	arr = (char **) malloc (sizeof(char *) * (ft_wcount(s, c, str_flag) + 1));
	if (arr == 0 || s == 0)
		return (NULL);
	return (ft_store_words(s, c, arr, str_flag));
}

// int	main(void)
// {
// 	int	nbr;
// 	nbr = 0;
// 	char *str = "Hallo this \"is a\" test";
// 	nbr = ft_wcount(str, ' ', '"');
// 	ft_printf("%d\n", nbr);
// 	return (0);
// }
// int	main(int ac, char *av[])
// {
// 	int	nbr;
// 	nbr = 0;
// 	if (ac > 1)
// 		nbr = ft_wcount(av[1], ' ', '"');
// 	ft_printf("%d\n", nbr);
// 	return (0);
	
	// char **string;
	// int	i;
	// int j;

	// i = 0;
	// j = 0;
	// if (ac > 1)
	// {
	// 	string = ft_tokenize(av[1], ' ', '"');
	// 	while (string[i])
	// 	{
	// 		ft_printf("%s\n", string[i]);
	// 		i++;
	// 	}
	// 	while (string[j])
	// 	{
	// 		free(string[j]);
	// 		string[j] = NULL;
	// 		j++;
	// 	}
	// 	free(string);
	// 	string = NULL;
	// }
	// return (0);
// }
