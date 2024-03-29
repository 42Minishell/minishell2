/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:12:24 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/02/16 19:17:43 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 28-02-21.

#include "env.h"
#include "minishell.h"

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

	klen = ft_strlen(key);
	vlen = ft_strlen(val);
	str = ft_malloc(klen + vlen + 2 * sizeof(char));
	ft_strlcpy(str, key, klen + vlen + 2);
	ft_strlcpy(str + klen, "=", vlen + 2);
	ft_strlcpy(str + klen + 1, val, vlen + 1);
	*(char **)data = str;
	return (data + sizeof(char *));
}

t_env	*env_init(void)
{
	t_env	*env;

	env = ft_calloc(1, sizeof(t_env));
	env->env_hashtable = bucket_new_table();
	env_update_envp(env);
	return (env);
}

void	env_free(t_env *env)
{
	env_free_envp(env);
	bucket_free_table(env->env_hashtable);
	free(env);
}

void	env_update_envp(t_env *env)
{
	char	**envp;

	if (env->envp)
		env_free_envp(env);
	envp = ft_calloc(HASHTABLE_SIZE, sizeof(char *) + 1);
	bucket_iter(env->env_hashtable, &env_iterator_envp, envp);
	env->envp = envp;
}
