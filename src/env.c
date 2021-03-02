// Created by Tom Jans on 28-02-21.

#include "env.h"

static void	env_free_envp(t_env *env)
{
	char	**envp;

	envp = env->envp;
	while (*envp)
	{
		free(*envp);
		envp++;
	}
	free(env->envp);
}

static void	*env_iterator_envp(char *key, char *val, void *data)
{
	char	*str;
	size_t	klen;
	size_t	vlen;

	klen = strlen(key);
	vlen = strlen(val);
	str = malloc(klen + vlen + 2 * sizeof(char));
	strncpy(str, key, klen);
	strncpy(str + klen, "=", 1);
	strncpy(str + klen + 1, val, vlen + 1);
	*(char **)data = str;
	return (data + sizeof(char *));
}

t_env	*env_init(void)
{
	t_env	*env;

	env = calloc(1, sizeof(t_env));
	env->env = bucket_new_table();
	env_update_envp(env);
	return (env);
}

void	env_free(t_env *env)
{
	env_free_envp(env);
	bucket_free_table(env->env);
	free(env);
}

void	env_update_envp(t_env *env)
{
	char	**envp;

	if (env->envp)
		env_free_envp(env);
	envp = calloc(HASHTABLE_SIZE, sizeof(char *) + 1);
	bucket_iter(env->env, &env_iterator_envp, envp);
	env->envp = envp;
}
