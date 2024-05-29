/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:45:02 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/29 16:19:18 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks for any syntax errors within the user input. 39 = single quote (')*/
int	not_valid_input(char *input)
{
	int	i;
	int	d_quotes;
	int	s_quotes;

	i = 0;
	d_quotes = 0;
	s_quotes = 0;
	while (input[i])
	{
		if (input[i] == '"')
			d_quotes++;
		if (input[i] == 39)
			s_quotes++;
		if ((input[i] == '<' && !input[i + 1])
			|| (input[i] == '>' && !input[i + 1])
			|| (input[i] == '|' && !input[i + 1]))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (1);
		}
		if ((input[i] == '<' && input[i + 1] == '|')
			|| (input[i] == '>' && input[i + 1] == '|')
			|| (input[i] == '|' && input[i + 1] == '|'))
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (1);
		}
		i++;
	}
	if (d_quotes != 0 && d_quotes % 2 != 0)
	{
		printf("minishell: syntax error, unclosed double quotes\n");
		return (1);
	}
	if (s_quotes != 0 && s_quotes % 2 != 0)
	{
		printf("minishell: syntax error, unclosed single quotes\n");
		return (1);
	}
	return (0);
}
