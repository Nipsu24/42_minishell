/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_quotes_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 12:12:59 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/09 11:14:18 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*returns 1, if double quotes left of character are an odd number,
  returns 2, if double quotes left of character are an even number*/
static int	count_d_quotes_left(char *input, int pos)
{
	int	d_quotes;

	d_quotes = 0;
	while (pos >= 0)
	{
		if (input[pos] == '"')
			d_quotes++;
		pos--;
	}
	if (d_quotes != 0)
	{
		if (d_quotes % 2 == 0)
			return (2);
		else if (d_quotes % 2 != 0)
			return (1);
	}
	return (0);
}

/*returns 1, if double quotes right of character are an odd number,
  returns 2, if double quotes right of character are an even number*/
static int	count_d_quotes_right(char *input, int pos)
{
	int	d_quotes;

	d_quotes = 0;
	while (input[pos])
	{
		if (input[pos] == '"')
			d_quotes++;
		pos++;
	}
	if (d_quotes != 0)
	{
		if (d_quotes % 2 == 0)
			return (2);
		else if (d_quotes % 2 != 0)
			return (1);
	}
	return (0);
}

/*returns 1, if single quotes left of character are an odd number,
  returns 2, if single quotes left of character are an even number*/
static int	count_s_quotes_left(char *input, int pos)
{
	int	s_quotes;

	s_quotes = 0;
	while (pos >= 0)
	{
		if (input[pos] == 39)
			s_quotes++;
		pos--;
	}
	if (s_quotes != 0)
	{
		if (s_quotes % 2 == 0)
			return (2);
		else if (s_quotes % 2 != 0)
			return (1);
	}
	return (0);
}

/*returns 1, if single quotes right of character are an odd number,
  returns 2, if single quotes right of character are an even number*/
static int	count_s_quotes_right(char *input, int pos)
{
	int	s_quotes;

	s_quotes = 0;
	while (input[pos])
	{
		if (input[pos] == 39)
			s_quotes++;
		pos++;
	}
	if (s_quotes != 0)
	{
		if (s_quotes % 2 == 0)
			return (2);
		else if (s_quotes % 2 != 0)
			return (1);
	}
	return (0);
}

/*Checks if character of str 'input' is at position 'pos' between single/double
  quotes. If count_quotes function returns an odd number (symbolised by 1) on 
  the left side of character, it is in quotes, unless there are no quotes on the 
  right site of it (symbolised by 0)*/
int	between_quotes(char *input, int pos)
{
	if (!input || !(*input))
		return (0);
	if ((count_d_quotes_left(input, pos) == 1)
		&& (count_d_quotes_right(input, pos) != 0))
		return (1);
	if ((count_s_quotes_left(input, pos) == 1)
		&& (count_s_quotes_right(input, pos) != 0))
		return (2);
	else
		return (0);
}

// echo "$USER"
// echo '$USER'