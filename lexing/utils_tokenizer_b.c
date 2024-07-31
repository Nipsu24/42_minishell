/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:21:38 by mmeier            #+#    #+#             */
/*   Updated: 2024/07/29 11:24:24 by mmeier           ###   ########.fr       */
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
void	w_count_quote_iter(char *s, int *i)
{
	(*i)++;
	while (s[*i] && !is_quote(s[*i]))
		(*i)++;
}
