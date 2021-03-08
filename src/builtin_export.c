// Created by Tom Jans on 05-03-21.

#include "minishell.h"
#include "builtins.h"

static void	add_env(char *argv, t_env *env)
{
	char	**split;
	void	*sfree;
	char	*key;
	char	*value;

	split = ft_split(argv, '=');
	if (split[1])
	{
		key = split[0];
		value = split[1];
		bucket_add(env->env, key, value);
	}
	sfree = split;
	while (*split)
	{
		split++;
		free(*(split-1));
	}
	free(sfree);
}

int	builtin_export(int argc, char **argv, t_state *state)
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
		add_env(argv[i], state->env);
		i++;
	}
	env_update_envp(state->env);
	return (0);
}