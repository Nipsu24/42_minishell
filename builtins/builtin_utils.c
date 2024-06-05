/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:21:17 by cesasanc          #+#    #+#             */
/*   Updated: 2024/06/05 15:34:52 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	needs_arg(char **comand_array)
{
	if (comand_array[0][0] == )

	if (!ft_strncmp("pwd", comand_array[0][0], 3)
		|| !ft_strncmp("cd", comand_array[0][0], 2))
		return(TRUE);
}