/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:49 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/03/02 21:04:02 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 01-03-21.

#include "minishell.h"

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
		bucket_add(env->env_hashtable, key, value);
	}
	sfree = split;
	while (*split)
	{
		split++;
		free(*(split - 1));
	}
	free(sfree);
}

void	env_populate(t_env *env, char *shell, char **envp)
{
	while (*envp)
	{
		add_env(*envp, env);
		envp++;
	}
	bucket_add(env->env_hashtable, "SHELL", shell);
	env_update_envp(env);
}

void	env_init_pwd(t_env *env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		exit(1);
	bucket_add(env->env_hashtable, "PWD", pwd);
	env_update_envp(env);
	free(pwd);
}

void	state_init(t_state *state, char **argv, char **envp)
{
	char	*shlvl;

	state->env = env_init();
	env_populate(state->env, *argv, envp);
	env_init_pwd(state->env);
	shlvl = bucket_get_value(state->env->env_hashtable, "SHLVL");
	if (shlvl == NULL)
		bucket_add(state->env->env_hashtable, "SHLVL", "1");
	else
	{
		shlvl = ft_itoa(ft_atoi(shlvl) + 1);
		bucket_add(state->env->env_hashtable, "SHLVL", shlvl);
		free(shlvl);
	}
	state->ret = 0;
}

void	state_free(t_state *state)
{
	env_free(state->env);
}
