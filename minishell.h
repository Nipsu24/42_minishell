/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:39:08 by mmeier            #+#    #+#             */
/*   Updated: 2024/09/06 11:04:39 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# define BUFF_SIZE 4096

extern bool	g_sigint;

/*Relevant tokens for lexing and parsing part.
  INIT_VAL for initial initiation when matching
  with strings of 2d input array.*/
typedef enum s_token_type
{
	INIT_VAL = -1,
	COMMAND,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	REDIRECT_OUT_APP,
	PIPE,
	RED_OP,
}			t_token_type;

/*Holds information of a single token*/
typedef struct s_token
{
	t_token_type	type;
}				t_token;

/*Struct containing relevant data of a process (one pipe).
  cmd contains command and its arguments.
  redir contains all redirect operators (<, >, <<, >>) of a
  pipe. Every operator is always followd by the filename as 
  the next string in the array. here_name is name of temporary
  heredoc file, here_tmp is content of heredoc file.*/
typedef struct s_prc
{
	char				**cmd;
	char				**redir;
	char				*path;
	int					*fd;
	int					fd_amount;
	char				*here_name;
	char				*here_tmp;
}				t_prc;

/*Overall struct for all relevant data of the shell*/
typedef struct s_data
{
	char		**temp_env;
	char		**tokens;
	char		*input;
	int			count_cmd;
	int			count_other;
	int			proc_nbr;
	int			num_tokens;
	int			i;
	int			j;
	int			k;
	int			l;
	int			m;
	int			err_flag;
	char		**path_arr;
	int			save_stdout;
	int			save_stdin;
	char		*nl;
	int			return_val;
	char		*tmp;
	int			*pid_arr;
	int			**fd_arr;
	char		oldpwd[BUFF_SIZE];
	char		newpwd[BUFF_SIZE];
	int			exit_status;
	int			delim_fst_line;
	int			exit_expand;
	char		*before;
	char		*after;
	int			flag_before;
	int			flag_after;
	int			pipe_flag;
	t_token		*token_list;
	int			flag_cntlr_d;
	t_prc		*proc;
}				t_data;

/*free functions*/

void		free_all(t_data *data, int exit_flag);
char		**free_arr_rev(char ***av, int j);
char		**free_arr(char ***arr);
void		free_arr_void(char ***arr);
int			free_proc_arr_rev(t_data *data);
void		free_proc_structs(t_data *data);
void		free_str(char **str);
void		free_int_arr(int **arr);
void		free_2d_int_arr(t_data *data, int ***arr);
void		free_2d_int_arr_rev(int ***arr, int j);

/*Error check and utils*/

int			not_valid_input(char *str, t_data *data);
int			check_quotes(char *input);
int			between_quotes(char *input, int pos);
int			write_sytx_error(char *error_str, char error);
int			check_red_out_app(char *input, int i);
int			check_heredoc_err(char *input, int i);
int			check_pipes(char *input);
int			is_quote(char c);

/*lexing*/

int			lexer(t_data *data);
int			insert_space(t_data *data);
int			ft_expand(t_data *data);
int			cut_var(t_data *data, int start, int len);
int			incl_exp_var(t_data *data, int start, char *exp_var, int len);
char		*get_expansion(t_data *data, char *tmp);
int			var_exist(t_data *data, char *tmp);
int			create_null_string(t_data *data);
int			check_before_after_case(t_data *data);
char		**ft_tokenize(char *s);
int			ft_wcount(char *s);
int			ft_malloc_token(t_data *data);
void		assign_token_type(t_data *tokens, int i);
int			remove_quotes(t_data *data);

/*parsing*/

int			parsing(t_data *data);
int			init_proc_structs(t_data *data);
int			alloc_proc_structs(t_data *data);
int			fill_proc_structs(t_data *data);
int			count_pipes(t_data *data);
void		helper_alloc_fds(t_data *data);
int			init_path(t_data *data);
int			join_cmd_path(t_data *data);
int			alloc_here_filename(t_data *data);
int			create_heredocs(t_data *data);
int			file_create_n_write(t_data *data);

/*execution*/

int			exec_proc(t_data *data);
int			redout_loop(t_data *data);
int			appendout_loop(t_data *data);
int			redin_loop(t_data *data);
int			here_redirect(t_data *data);
int			no_other_redout(t_data *data);
int			no_other_redin(t_data *data);
int			no_other_heredoc(t_data *data);
void		delete_heredocs(t_data *data);
int			init_pid_arr(t_data *data);
int			init_fd_arr(t_data *data);
int			child_procs(t_data *data);
int			child_exec(t_data *data);
int			heredoc_exec(t_data *data);
int			redir_exec(t_data *data);
void		parent_close_fds(t_data *data);
void		parent_wait_n_cleanup(t_data *data);
int			parent_builtin_check(t_data *data);
int 		check_value_of_errno(t_data *data, char *file_name);

/*built-in utils*/

int			len_array(char **array);
int			find_var(char **env, char *var);
int			add_var(t_data *data, char *var);
int			update_var(t_data *data, char *var);
char		*get_env_var(t_data *data, char *var);

/*built-ins*/

char		**ft_copy_env(char **env, t_data *data);
int			child_builtins(t_data *data);
int			non_child_builtins(t_data *data);
int			cd(char **array, t_data *data);
int			cd_home(t_data *data);
void		print_env(t_data *data);
int			update_shlvl(t_data *data);
int			echo(t_data *data);
int			pwd(t_data *data);
int			unset(t_data *data);
int			export(t_data *data);
int			do_exit(t_data *data);

/*signals*/

void		handle_signals(int sig);
void		setup_signal(void);
void		setup_termios(int mode);
void		here_sig_int(int sig);

/*further functions*/

void		init_data(t_data *data);
void		init_index(t_data *data);

#endif