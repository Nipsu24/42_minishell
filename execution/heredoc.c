/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeier <mmeier@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:11:03 by mmeier            #+#    #+#             */
/*   Updated: 2024/08/05 16:51:46 by mmeier           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_data *data)
{
	char	*delimiter;
	char	*new_line;

	delimiter = NULL;
	new_line = "\n";
	if (ft_strncmp(data->proc[data->j].redir[data->l], "<<", 2) == 0)
	{
		delimiter = ft_strjoin(new_line, data->proc[data->j].redir[data->l + 1]);
		if (!delimiter)
			return (1);
		while (ft_strncmp(data->proc[data->j].here_tmp, delimiter, ft_strlen(delimiter)) != 0)
		{
			printf("> ");
			data->proc[data->j].here_tmp = get_next_line(STDIN_FILENO);
			if (!data->proc[data->j].here_tmp)
				return (1);
		}
		printf("READ STRING IS: %s", data->proc[data->j].here_tmp);
		printf("DELIMETER: %s\n", delimiter);
	}
	printf("DELIMETER: %s\n", delimiter);
	return (0);
}	
		
		
// 		data->proc[data->j].fd[data->k]
// 			= open(data->proc[data->j].redir[data->i + 1], O_RDONLY);
// 		if (data->proc[data->j].fd[data->k] < 0)
// 		{
// 			printf("%s: No such file or directory\n",
// 				data->proc[data->j].redir[data->i + 1]);
// 			return (1);
// 		}
// 		if (no_other_redin(data))
// 		{
// 			dup2(data->proc[data->j].fd[data->k], STDIN_FILENO);
// 			close(data->proc[data->j].fd[data->k]);
// 			if (data->proc[data->j].redir[data->i + 2] != NULL)
// 				data->proc[data->j].fd[data->k]++;
// 			return (0);
// 		}
// 		else
// 		{
// 			close (data->proc[data->j].fd[data->k]);
// 			data->proc[data->j].fd[data->k]++;
// 		}
// 	}
// 	return (0);
// }
