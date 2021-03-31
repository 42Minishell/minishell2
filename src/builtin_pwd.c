// Created by Tom Jans on 28-03-21.

#include "builtins.h"

int	builtin_pwd(int argc, char **argv, t_state *state)
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
