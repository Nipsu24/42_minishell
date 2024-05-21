/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:39:08 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/21 17:14:20 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum s_token_type
{
	COMMAND,
	STRING,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_IN_DEL,
	REDIRECT_OUT_APP,
	FILE_NAME,
	PIPE,
	ENVAR,
}			t_token_type;

typedef struct s_token
{
	char			*cnt;
	t_token_type	type;
}				t_token;

typedef struct s_tokens
{
	int			index;
	t_token		*entry;	
}				t_tokens;

typedef struct s_data
{
	char		**temp_env;
	char		**tokens;
	char		*input;
	t_tokens	*token_list;
}				t_data;

int		ft_input(t_data *data);
void	print_env(char **env);
char	**ft_tokenize(char const *s, char c, char str_flag);
void	ft_token_type(t_data *tokens, int i);
void	free_all(t_data *data);

#endif