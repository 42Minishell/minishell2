// Created by Tom Jans on 05-03-21.

#include "minishell.h"
#include "builtins.h"

int	builtin_unset(int argc, char **argv, t_state *state)
{
	int i;

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
