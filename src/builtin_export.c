/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:36 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/03/23 21:41:41 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 05-03-21.

#include "minishell.h"
#include "builtins.h"
#include "ipc.h"

static void	add_env(char *argv, int ipc[2])
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
		send_ipc(ipc[1], ENV_ADD, key, value);
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
	int		i;
	int		exit_code;

	i = 1;
	exit_code = 0;
	if (ft_strncmp("env", *argv, 4) == 0 || argc < 2)
		bucket_iter(state->env->env, &print_env, NULL);
	else
	{
		while (i < argc)
		{
			if (argv[i] && argv[i][0] && ft_isdigit(argv[i][0]) == true)
			{
				printf("export: `%.*s': not a valid identifier\n",
					(int)ft_strclen(argv[i], '='), argv[i]);
				exit_code = 1;
			}
			else
				add_env(argv[i], ipc);
			i++;
		}
	}
	send_ipc_int(ipc[1], END_IPC, 0);
	exit(exit_code);
}
