/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:39:08 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/20 16:32:21 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_placeholder
{
	int		placeholder;
}				t_placeholder;

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

int		ft_input(char **env);
void	print_env(char **env);
char	**ft_tokenize(char const *s, char c, char str_flag);
void	ft_token_type(t_tokens *tokens, int i);

#endif