// Created by Tom Jans on 01-03-21.

#include <errno.h>
#include "minishell.h"

static char	*resolve_local(char *exec)
{
	struct stat	result;

	if (stat(exec, &result) == -1)
		return (NULL);
	if (S_ISDIR(result.st_mode))
	{
		errno = EISDIR;
		return (NULL);
	}
	return (ft_strdup(exec));
}

char	*path_resolve(t_env *env, char *exec)
{
	char	*presolve;

	if (*exec == '/' || *exec == '.')
		return (resolve_local(exec));
	presolve = env_path_lookup(env, exec);
	if (presolve)
		return (presolve);
	return (NULL);
}
