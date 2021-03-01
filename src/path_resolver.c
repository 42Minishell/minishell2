// Created by Tom Jans on 01-03-21.

#include "minishell.h"

char	*find_binary(char **dirs, char *exec)
{
	struct stat	result;
	size_t		dlen;
	char		path[255];

	if (!*dirs)
		return (NULL);
	dlen = ft_strlen(*dirs);
	ft_strlcpy(path, *dirs, 255);
	path[dlen] = '/';
	ft_strlcpy(path + dlen + 1, exec, 255 - dlen - 1);
	if (stat(path, &result) != -1 && !S_ISDIR(result.st_mode))
		return (ft_strdup(path));
	return (find_binary(dirs + 1, exec));
}

static void	freedirs(char **dirs)
{
	void	*orig;

	orig = dirs;
	while (*dirs)
	{
		free(*dirs);
		dirs++;
	}
	free(orig);
}

char	*env_path_lookup(t_env *env, char *exec)
{
	char	*path;
	char	**dirs;
	char	*ret;

	path = bucket_get_value(env->env, "PATH");
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	ret = find_binary(dirs, exec);
	freedirs(dirs);
	return (ret);
}
