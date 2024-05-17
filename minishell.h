/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:39:08 by mmeier            #+#    #+#             */
/*   Updated: 2024/05/15 16:00:04 by mmeier           ###   ########.fr       */
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

int		ft_input(char **env);
void	print_env(char **env);
char	**ft_tokenize(char const *s, char c, char str_flag);

#endif
