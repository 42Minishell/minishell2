// Created by Tom Jans on 05-03-21.

#include "minishell.h"
#include "builtins.h"

int	builtin_unset(int argc, char **argv, t_state *state)
{
	if (argc != 2)
	{
		printf("%s: not enough arguments\n", argv[0]);
		return (-1);
	}
	bucket_del(state->env->env, argv[1]);
	env_update_envp(state->env);
	return (0);
}
