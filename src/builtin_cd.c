/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zinobias <zinobias@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:09:09 by zinobias      #+#    #+#                 */
/*   Updated: 2021/12/18 17:12:35 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
