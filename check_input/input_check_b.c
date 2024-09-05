/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 11:57:41 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/05 22:15:18 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Checks if there are unclosed single or double quotes within the user input.
  Quote != 0 means open quotes.*/
int	check_quotes(char *input)
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
		print_error("minishell", "syntax error, unclosed quotes");
		return (1);
	}
	return (0);
}

/*Prints several error messages depending on the error case. When calling 
  function, caller can pass respective custom *char or char to trigger 
  preferred message.*/
int	write_sytx_error(char *error_str, char error)
{
	if (error_str == NULL)
	{
		print_error("syntax error", "error near unexpected token:");
		write(STDERR_FILENO, &error, 1);
		write(STDERR_FILENO, "\n", 1);
		return (1);
	}
	if (!error)
	{
		print_error("syntax error", "error near unexpected token:");
		write(STDERR_FILENO, error_str, ft_strlen(error_str));
		write(STDERR_FILENO, "\n", 1);
		return (1);
	}
	return (0);
}

/*Checks if there are pipes next to each other in user input or empty pipes.
  If yes, prints respective error message.*/
int	check_pipes(char *input)
{
	int	i;

	i = 0;
	if (!input)
		return (0);
	while (input[i])
	{
		if (input[i] == '|' && !between_quotes(input, i))
		{
			i++;
			if (input[i] == '|')
				return (write_sytx_error("||", 0));
			if (!input[i] || input[i] == '<' || input[i] == '>')
				return (write_sytx_error(NULL, '|'));
			while (input[i] && input[i] == 32)
				i++;
			if (!input[i])
				return (write_sytx_error(NULL, '|'));
			if (input[i] && input[i] == '|')
				return (write_sytx_error(NULL, '|'));
		}
		i++;
	}
	return (0);
}

/*Checks for errors related to red_out_app operant
  with different constellations of operants*/
int	check_red_out_app(char *input, int i)
{
	i++;
	if (!input[i])
		return (write_sytx_error("newline", 0));
	while (input[i] && input[i] == 32)
		i++;
	if (!input[i])
		return (write_sytx_error("newline", 0));
	if (input[i] == '>' && input[i + 1] != '>')
		return (write_sytx_error(NULL, '>'));
	if (input[i] == '>' && input[i + 1] == '>')
		return (write_sytx_error(">>", 0));
	if (input[i] == '<')
		return (write_sytx_error(NULL, '<'));
	return (0);
}

/*Checks for errors related to heredoc with different
  constellations of operants*/
int	check_heredoc_err(char *input, int i)
{
	i++;
	if (!input[i])
		return (write_sytx_error("newline", 0));
	if (input[i] == '<')
		return (write_sytx_error("newline", 0));
	while (input[i] && input[i] == 32)
		i++;
	if (!input[i])
		return (write_sytx_error("newline", 0));
	if (input[i] == '<' && input[i + 1] != '>')
		return (write_sytx_error(NULL, '<'));
	if (input[i] == '<' && input[i + 1] == '>')
		return (write_sytx_error(NULL, '>'));
	if (input[i] == '>')
		return (write_sytx_error(NULL, '>'));
	return (0);
}
