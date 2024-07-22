/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:39:08 by mmeier            #+#    #+#             */
/*   Updated: 2024/07/22 15:43:26 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

/*Struct containing command structure extracted from tokens*/
typedef struct s_command
{
	char				*cnt;
	char				**args;
	char				*file_in;
	char				*file_out;
}				t_command;

/*Struct containing all command structures extracted from tokens*/
typedef struct s_com_lst
{
	t_command	*cmd;
}				t_com_lst;

typedef enum s_token_type
{
	COMMAND, //0
	REDIRECT_IN, //1
	REDIRECT_OUT, //2
	HEREDOC, //3
	REDIRECT_OUT_APP, //4
	PIPE, //5
	ENVAR, //6
	BUILTIN, //7
	REMOVE //8
}			t_token_type;

/*Holds information of a single token*/
typedef struct s_token
{
	//char			*cnt;
	t_token_type	type;
}				t_token;

/*Struct containing all tokens generated from user input*/
typedef struct s_tokens
{
	t_token		*entry;
	int			num;	
}				t_tokens;

/*Overall struct for all relevant data of the shell*/
typedef struct s_data
{
	char		**temp_env;
	char		**tokens;
	char		*input;
	int			pipe_count;
	char		**prcs_buf;
	char		**prcs;
	t_tokens	*token_list;
	t_com_lst	*cmds;
}				t_data;

void	print_env(char **env);
void	init_data(t_data *data);
char	**ft_tokenize(char const *s, char c, char str_flag);
void	ft_token_type(t_data *tokens, int i);
void	free_all(t_data *data);
int		ft_malloc_token(t_data *data);
char	**free_arr_rev(char **av, int j);
int		not_valid_input(char *str);
void	setup_signal(void);
int		between_quotes(char *input, int pos);
int		parse_cmds(t_data *data);
int		split_in_prcs(t_data *data);
char	**ft_free(char **result, size_t j);
char	**free_arr(char **arr);
int		trim_space(t_data *data);
int		ft_expand(t_data *data);

#endif