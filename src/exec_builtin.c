/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_builtin.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:36 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/02/23 16:02:05 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/signal.h>
#include "builtins.h"

static int	count_args(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	exec_builtin(t_state *state, t_token *token, char **argv)
{
	int	argc;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	argc = count_args(argv);
	token->result.builtin(argc, argv, state, token->ipc_fd);
	exit(0);
}
