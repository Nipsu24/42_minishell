/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenizer_b.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 11:21:38 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/10 16:34:10 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*returns double or single quote if character is respective symbol,
  otherwise 0.*/

int	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

/*Counts words in the input string split by spaces which are not in single
  or double quotation marks. sq/dq flags are set on/off depending on if 
  being in a quoted section. E.g. if in double quoted section (dq==1) and
  another '"' is encountered, dq is reset to 0.*/
int	ft_wcount(char *s)
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
			while (s[i] && (s[i] != ' ' || sq == 1 || dq == 1))
			{
				if (s[i] == '\'' && dq == 0)
					sq = !sq;
				else if (s[i] == '"' && sq == 0)
					dq = !dq;
				i++;
			}
		}
	}
	printf("WORD COUNT: %d\n", count);
	return (count);
}	
