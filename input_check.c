/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:45:02 by mmeier            #+#    #+#             */
/*   Updated: 2024/07/29 11:29:42 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks if there are unclosed single or double quotes within the user input.
  Quote != 0 means open quotes.*/
static int	check_quotes(char *input)
{
	char	quote;
	int		i;

	quote = 0;
	i = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			if (quote == input[i])
				quote = 0;
			else if (quote == 0)
				quote = input[i];
		}
		i++;
	}
	if (quote)
	{
		printf("minishell: syntax error, unclosed quotes\n");
		return (1);
	}
	return (0);
}

/*Prints several error messages depending on the error case. When calling 
  function, caller can pass respective int n as argument in order to trigger 
  preferred message.*/
static int	write_sytx_error(int n)
{
	if (n == 0)
	{
		printf("minishell: syntax error near unexpected token `||'\n");
		return (1);
	}
	if (n == 1)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (1);
	}
	if (n == 2)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

/*Checks if there are pipes next to each other in user input, if yes, prints 
  respective error message.*/
static int	check_pipes(char *input)
{
	int	i;

	i = 0;
	if (!input && !input[i])
		return (0);
	while (input[i])
	{
		if (input[i] == '|' && !between_quotes(input, i))
		{
			i++;
			if (input[i] == '|')
				return (write_sytx_error(0));
			if (!input[i] || input[i] == '<' || input[i] == '>')
				return (write_sytx_error(1));
			while (input[i] && input[i] == 32)
				i++;
			if (input[i] && input[i] == '|')
				return (write_sytx_error(1));
		}
		i++;
	}
	return (0);
}

/*Checks whether there is anything written after redirect operators or if a pipe
  is following a redirect operator. Prints respective error messages in those 
  cases.*/
static int	check_redirects(char *input)
{
	int	i;

	i = 0;
	if (!input && !input[i])
		return (0);
	while (input[i])
	{
		if ((input[i] == '<' && !between_quotes(input, i))
			|| (input[i] == '>' && !between_quotes(input, i)))
		{
			i++;
			if (!input[i] || input[i] == '|')
				return (write_sytx_error(2));
			while (input[i] && input[i] == 32)
				i++;
			if (!input[i])
				return (write_sytx_error(2));
			if (input[i] == '|')
				return (write_sytx_error(1));
		}
		i++;
	}
	return (0);
}

/*Checks for any syntax errors within the user input.*/
int	not_valid_input(char *input)
{
	if (check_quotes(input))
		return (1);
	if (check_pipes(input))
		return (1);
	if (check_redirects(input))
		return (1);
	return (0);
}
