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
#include "ipc.h"

static int	prterror(char *err, char *bin)
{
	printf("%s: %s\n", bin, err);
	return (1);
}

int	builtin_cd(int argc, char **argv, t_state *state, int ipc[2])
{
	char	*path;
	char	cwd[255];
	int		ret;

	if (argc < 2)
	{
		path = bucket_get_value(state->env->env, "HOME");
		if (!path)
			exit(prterror("HOME not set", *argv));
	}
	else
	{
		path = argv[1];
	}
	ret = chdir(path);
	if (ret)
		exit(prterror(strerror(errno), *argv));
	getcwd(cwd, 255);
	send_ipc(ipc[1], CHDIR, path, NULL);
	send_ipc(ipc[1], ENV_ADD, "PWD", cwd);
	send_ipc_int(ipc[1], END_IPC, 0);
	exit(0);
}
