#include "env.h"
#include "tests.h"
#include "libft.h"

static void	check_init(t_env *env)
{
	char	*val;

	uassert((bucket_get_value(env->env, "PATH") != NULL), "PATH is not set.");
	uassert((bucket_get_value(env->env, "TERM") != NULL), "TERM is not set.");
	val = bucket_get_value(env->env, "SHELL");
	uassert((val != NULL), "SHELL is not set.");
	uassert((ft_strncmp("test", val, 5) == 0), "SHELL is not test");
	uassert((bucket_get_value(env->env, "PWD") == NULL),
		"PWD should not be set.");
}

void	test_env(void)
{
	t_env	*env;

	env = env_init();
	uassert((env != NULL), "env_init returned NULL");
	env_populate(env, "test");
	check_init(env);
	env_init_pwd(env);
	uassert((bucket_get_value(env->env, "PWD") != NULL), "PWD is not set.");
	env_free(env);
}
