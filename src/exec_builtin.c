#include "builtins.h"

static int	count_args(char **argv)
{
	int i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

void	exec_builtin(t_state *state, t_token *token, char **argv)
{
	int argc;

	argc = count_args(argv);
	token->result.builtin(argc, argv, state, token->ipc_fd);
}