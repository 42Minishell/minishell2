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
#include "ipc.h"

int	builtin_unset(int argc, char **argv, t_state *state, int ipc[2])
{
	int	i;

	(void)state;
	i = 1;
	if (argc < 2)
	{
		printf("%s: not enough arguments\n", argv[0]);
		send_ipc_int(ipc[1], END_IPC, 0);
		return (-1);
	}
	while (i < argc)
	{
		send_ipc(ipc[1], ENV_DEL, argv[i], NULL);
		i++;
	}
	send_ipc_int(ipc[1], END_IPC, 0);
	exit(0);
}
