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

#include <unistd.h>
#include "builtins.h"
#include "ipc.h"

int	builtin_pwd(int argc, char **argv, t_state *state, int ipc[2])
{
	char	*pwd;

	(void)argc;
	(void)argv;
	(void)state;
	send_ipc_int(ipc[1], END_IPC, 0);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("%s: error retrieving current directory: %s\n", *argv, \
			strerror(errno));
		exit(1);
	}
	printf("%s\n", pwd);
	exit(0);
}
