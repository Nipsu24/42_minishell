/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:20:54 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/11 15:58:06 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*returns double or single quote if character is respective symbol,
  otherwise 0.*/

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

/*Helper function (used in ft_wcount and ft_store_words) which iterates
  through string as long as words are in quoted passages or as long as 
  there is no space which is not in quotes.*/
static void	iter_str_helper(char *s, int *i, int sq, int dq)
{
	while (s[*i] && (s[*i] != ' ' || sq == 1 || dq == 1))
	{
		if (s[*i] == '\'' && dq == 0)
			sq = !sq;
		else if (s[*i] == '"' && sq == 0)
			dq = !dq;
		(*i)++;
	}
}

/*Counts words in the input string split by spaces which are not in single
  or double quotation marks. sq/dq flags are set on/off depending on if 
  being in a quoted section. E.g. if in double quoted section (dq==1) and
  another '"' is encountered, dq is reset to 0.*/
static int	ft_wcount(char *s)
{
	int	i;
	int	count;
	int	dq;
	int	sq;

	i = 0;
	count = 0;
	dq = 0;
	sq = 0;
	if (s[i] == '\0')
		return (1);
	while (s[i])
	{
		while (s[i] == ' ' && sq == 0 && dq == 0)
			i++;
		if (s[i])
		{
			count++;
			iter_str_helper(s, &i, sq, dq);
		}
	}
	return (count);
}	

/*Populates strings in 2d token array. Strings are split by spaces
  which are not in quotes.*/
static char	**ft_store_words(char *s, char **arr, t_data *data)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	start = 0;
	data->dq = 0;
	data->sq = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == ' ' && data->sq == 0 && data->dq == 0)
			i++;
		if (s[i])
		{
			start = i;
			iter_str_helper(s, &i, data->sq, data->dq);
			arr[j] = ft_substr(s, start, (i - start));
			if (!arr[j])
				return (free_arr_rev(&arr, j));
			j++;
		}
	}
	arr[j] = 0;
	return (arr);
}

/*Modification of ft_split. Splits input into array of strings delimited
  by spaces which are not in quotes.*/
char	**ft_tokenize(char *s, t_data *data)
{
	char	**arr;

	if (!s)
		return (0);
	arr = (char **) malloc (sizeof(char *) * (ft_wcount(s) + 1));
	if (arr == 0 || s == 0)
		return (NULL);
	if (s[0] == '\0')
	{
		arr[0] = ft_strdup("");
		if (!arr[0])
			return (free_arr_rev(&arr, 0));
		arr[1] = 0;
		return (arr);
	}
	return (ft_store_words(s, arr, data));
}
