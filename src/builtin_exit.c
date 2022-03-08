/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:35 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/03/08 16:50:05 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ipc.h"

int	builtin_exit(int argc, char **argv, t_state *state, int ipc[2])
{
	int	exit_no;

	(void)state;
	if (argc < 2)
	{
		send_ipc_int(ipc[1], EXIT, 0);
		exit(0);
	}
	exit_no = ft_atoi(argv[1]);
	while (*argv[1])
	{
		if (!ft_isdigit(*argv[1]))
		{
			printf("%s: numeric argument required\n", *argv);
			send_ipc_int(ipc[1], EXIT, 255);
			exit(2);
		}
		argv[1]++;
	}
	send_ipc_int(ipc[1], EXIT, exit_no);
	exit(exit_no);
}
