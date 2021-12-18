/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:39 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:13:40 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 05-03-21.

#include "minishell.h"
#include "builtins.h"

int	builtin_unset(int argc, char **argv, t_state *state)
{
	int	i;

	i = 1;
	if (argc < 2)
	{
		printf("%s: not enough arguments\n", argv[0]);
		return (-1);
	}
	while (i < argc)
	{
		bucket_del(state->env->env, argv[i]);
		i++;
	}
	env_update_envp(state->env);
	return (0);
}
