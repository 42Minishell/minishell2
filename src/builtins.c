/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:41 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:13:42 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 05-03-21.

#include "builtins.h"

static const t_function_lookup	g_lookup_table[8] = {
{"unset", &builtin_unset},
{"export", &builtin_export},
{"echo", &builtin_echo},
{"env", &builtin_export},
{"pwd", &builtin_pwd},
{"cd", &builtin_cd},
{"exit", &builtin_exit},
{"", NULL},
};

void	*find_builtin_func(char *exec)
{
	size_t	i;
	size_t	e_len;

	i = 0;
	e_len = ft_strlen(exec);
	while (g_lookup_table[i].func_ptr)
	{
		if (ft_strncmp(exec, g_lookup_table[i].exec, e_len + 1) == 0)
			return (g_lookup_table[i].func_ptr);
		i++;
	}
	return (NULL);
}
