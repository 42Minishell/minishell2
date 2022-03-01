/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   resolver.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:14:00 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:15:25 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 01-03-21.

#include <errno.h>
#include "minishell.h"
#include "builtins.h"

static t_resolve_result_type	resolve_local(char *exec, char **dest)
{
	struct stat	result;

	if (stat(exec, &result) == -1)
		return (NOTFOUND);
	if (S_ISDIR(result.st_mode))
	{
		errno = EISDIR;
		return (NOTFOUND);
	}
	*dest = ft_strdup(exec);
	return (EXTERNAL_BINARY);
}

t_resolve_result_type	path_resolve(t_env *env, char *exec,
							t_resolve_result *result)
{
	char	*presolve;
	void	*builtin;

	if (*exec == '/' || *exec == '.')
		return (resolve_local(exec, &result->path));
	builtin = find_builtin_func(exec);
	if (builtin)
	{
		result->builtin = builtin;
		return (BUILTIN);
	}
	presolve = env_path_lookup(env, exec);
	if (presolve)
	{
		result->path = presolve;
		return (EXTERNAL_BINARY);
	}
	return (NOTFOUND);
}

int	path_resolve_token_list(t_env *env, t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == executable || tokens->type == redirect_to_pipe)
		{
			tokens->result_type = \
				path_resolve(env, tokens->token, &tokens->result);
			if (tokens->result_type == NOTFOUND)
			{
				tokens->result_type = EXTERNAL_BINARY;
				tokens->result.path = ft_strdup("");
			}
		}
		tokens = tokens->next;
	}
	return (0);
}
