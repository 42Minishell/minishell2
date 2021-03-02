// Created by Tom Jans on 01-03-21.

#include "minishell.h"

static void	prtenv(t_env *env)
{
	char	**envp;

	env_update_envp(env);
	envp = env->envp;
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
}

char	*prompt(t_state *state)
{
	char	*ret;

	write(1, "MS > ", 6);
	if (fd_readline(state->sin, &ret) == -1)
		return (NULL);
	if (ft_strncmp(ret, "exit", 5) == 0)
	{
		free(ret);
		return (NULL);
	}
	if (ft_strncmp(ret, "_env", 5) == 0)
	{
		free(ret);
		prtenv(state->env);
		errno = 0;
		return (strdup(""));
	}
	return (ret);
}
