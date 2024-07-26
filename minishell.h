/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:39:08 by mmeier            #+#    #+#             */
/*   Updated: 2024/07/25 13:44:30 by mmeier           ###   ########.fr       */
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
	INIT_VAL = -1,
	COMMAND, //0
	REDIRECT_IN, //1
	REDIRECT_OUT, //2
	HEREDOC, //3
	REDIRECT_OUT_APP, //4
	PIPE, //5
	ENVAR, //6
	BUILTIN, //7 not yet handled
	RED_OP, //8
}			t_token_type;

/*Holds information of a single token*/
typedef struct s_token
{
	t_token_type	type;
}				t_token;

/*Struct containing relevant data of a process (one pipe)*/
typedef struct s_prc
{
	char				**cmd;
	char				**redir; // < > << >>
}				t_prc;

/*Overall struct for all relevant data of the shell*/
typedef struct s_data
{
	char		**temp_env;
	char		**tokens;
	char		*input;
	int			pipe_count;
	char		**prcs_buf;
	char		**prcs;
	int			count_cmd;
	int			count_other;
	int			proc_nbr;
	int			i;
	int			j;
	int			k;
	int			l;
	t_token		*token_list;
	t_prc		*proc;
}				t_data;

/*free functions*/
void	free_all(t_data *data);
char	**free_arr_rev(char **av, int j);
char	**ft_free(char **result, size_t j);
char	**free_arr(char **arr);
int		free_proc_arr_rev(t_data *data);

/*init and malloc functions*/
void	init_data(t_data *data);
int		ft_malloc_token(t_data *data);
int		init_proc_structs(t_data *data);

/*Error check and utils*/
int		not_valid_input(char *str);
int		between_quotes(char *input, int pos);

/*parsing*/
char	**ft_tokenize(char const *s);
//char	**ft_tokenize(char const *s, char c, char str_flag);
void	assign_token_type(t_data *tokens, int i);
int		ft_expand(t_data *data);
int		insert_space(t_data *data);

/*further functions*/
void	setup_signal(void);
void	print_env(char **env);
int		split_in_prcs(t_data *data);

#endif