/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:37 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:13:38 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 28-03-21.

#include "builtins.h"

int	builtin_pwd(int argc, char **argv, t_state *state, int ipc[2])
{
	char	*pwd;

	(void)argc;
	(void)argv;
	pwd = bucket_get_value(state->env->env, "PWD");
	if (!pwd)
		return (1);
	printf("%s\n", pwd);
	return (0);
}
