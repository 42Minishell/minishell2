/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:36 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:13:37 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 05-03-21.

#include "minishell.h"
#include "builtins.h"

void	add_env(char *argv, t_env *env)
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
		free(*(split - 1));
	}
	free(sfree);
}

static void	*print_env(char *key, char *value, void *data)
{
	(void)data;
	printf("%s=%s\n", key, value);
	return (NULL);
}

int	builtin_export(int argc, char **argv, t_state *state, int ipc[2])
{
	int	i;

	i = 1;
	if (ft_strncmp("env", *argv, 4) == 0 || argc < 2)
	{
		bucket_iter(state->env->env, &print_env, NULL);
		return (0);
	}
	while (i < argc)
	{
		add_env(argv[i], state->env);
		i++;
	}
	env_update_envp(state->env);
	return (0);
}
