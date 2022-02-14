/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:36 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:13:37 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

	argc = count_args(argv);
	token->result.builtin(argc, argv, state, token->ipc_fd);
	exit(0);
}
