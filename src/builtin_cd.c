#include "builtins.h"

static int	prterror(char *err, char *bin)
{
	printf("%s: %s\n", bin, err);
	return (1);
}

int	builtin_cd(int argc, char **argv, t_state *state)
{
	char	*path;
	char	cwd[255];
	int		ret;

	if (argc < 2)
	{
		path = bucket_get_value(state->env->env, "HOME");
		if (!path)
			return (prterror("HOME not set", *argv));
	}
	else
	{
		path = argv[1];
	}
	ret = chdir(path);
	if (ret)
		return (prterror(strerror(errno), *argv));
	getcwd(cwd, 255);
	bucket_add(state->env->env, "PWD", cwd);
	return (0);
}
