/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:21:38 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/28 11:09:18 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*returns double or single quote if character is respective symbol,
  otherwise 0.*/

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

/*Helper function of ft_wcount, iterates through quoted part of string*/
static void	w_count_quote_iter(char *s, int *i)
{
	(*i)++;
	while (s[*i] && !is_quote(s[*i]))
		(*i)++;
}

/*Helper function of ft_wcount*/
static void	iter_quotes_n_non_quotes(char *s, int *i)
{
	while (s[*i] && s[*i] != ' ')
	{
		if ((is_quote(s[*i]) && s[*i + 1]))
			w_count_quote_iter(s, i);
		if (s[*i])
			(*i)++;
	}
}

/*Counts words (and strings in quotes as one single word)*/
int	ft_wcount(char *s)
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
				iter_quotes_n_non_quotes(s, &i);
			}
			while (s[i] && s[i] == ' ')
				i++;
		}
	}
	return (count);
}
