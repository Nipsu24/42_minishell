/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 16:24:39 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/20 16:56:23 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	ft_token_type(t_tokens *tokens, int i)
{
	if (tokens->entry[i].cnt[0] == '"')
		tokens->entry[i].type = STRING;
	else if (!ft_strncmp(tokens->entry[i].cnt, "<\0", 2))
		tokens->entry[i].type = REDIRECT_IN;
	else if (!ft_strncmp(tokens->entry[i].cnt, ">\0", 2))
		tokens->entry[i].type = REDIRECT_OUT;
	else if (tokens->entry[i].cnt[0] == '|')
		tokens->entry[i].type = PIPE;
	else if (!ft_strncmp(tokens->entry[i].cnt, "<<\0", 2))
		tokens->entry[i].type = REDIRECT_IN_DEL;
	else if (!ft_strncmp(tokens->entry[i].cnt, ">>\0", 2))
		tokens->entry[i].type = REDIRECT_OUT_APP;
	else if ((tokens->entry[i].cnt[i - 1] == '<') ||
		(tokens->entry[i].cnt[i - 1] == '>'))
		tokens->entry[i].type = FILE_NAME;
	else if (tokens->entry[i].cnt[0] == '$')
		tokens->entry[i].type = ENVAR;
	else
		tokens->entry[i].type = COMMAND;	
}

/*The 'readline' function enables writing commands to program during execution. 
  In case 'env' is typed to shell, env. variables are printed to the terminal, 
  otherwise command that user inputs is printed. The 'add_history' function 
  enables visibility of previous inserted commands (using keyboards "arrow up" 
  after a command has been typed)*/
int	ft_input(char **env)
{
	// t_tokens	token_table;
	char		*input;
	char		*environment;
	char		**tokens;
	int			i;
	int			j;

	i = 0;
	j = 0;
	environment = "env";
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("EOF or ERROR");
			return (1);
		}
		if (ft_strncmp(input, environment, 3) == 0)
			print_env(env);
		else
			printf("You entered %s\n", input);
		if (ft_strlen(input) > 0)
			add_history(input);
		tokens = ft_tokenize(input, ' ', '"');
		if (!tokens)
			return (1);
		while (tokens[i])
		{
			
			ft_printf("%s\n", tokens[i]);
			// token_table.entry[i].cnt = tokens[i];
			// ft_token_type(&token_table, i);
			// ft_printf("%s\n", token_table.entry[i].cnt);
			// ft_printf("%d\n", token_table.entry[i].type);
			i++;
		}
		i = 0;
		free(input);
		input = NULL;
		while (tokens[j])
		{
			free(tokens[j]);
			tokens[j] = NULL;
			j++;
		}
		j = 0;
		free(tokens);
		tokens = NULL;
	}
	return (0);
}

/*String array 'env' holds by default environment variables of the system. 
  Array still needs to be copied before doing any alterations, but it's 
  already possible to print it. */
int	main(int ac, char *av[], char *env[])
{
	if (ac > 1 || av[1])
	{
		printf("Error. File does not take input.\n");
		return (1);
	}
	else
		ft_input(env);
	return (0);
}
