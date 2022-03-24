/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zinobias <zinobias@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:09:09 by zinobias      #+#    #+#                 */
/*   Updated: 2022/03/02 21:03:52 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "ipc.h"

static int	prterror(char *err, char *bin, int ipc[2])
{
	printf("%s: %s\n", bin, err);
	send_ipc_int(ipc[1], END_IPC, 0);
	return (1);
}

int	builtin_cd(int argc, char **argv, t_state *state, int ipc[2])
{
	char	*path;
	char	*cwd;
	int		ret;

	if (argc < 2)
	{
		path = bucket_get_value(state->env->env_hashtable, "HOME");
		if (!path)
			exit(prterror("HOME not set", *argv, ipc));
	}
	else
		path = argv[1];
	ret = chdir(path);
	cwd = getcwd(NULL, 0);
	if (!cwd || ret)
		exit(prterror(strerror(errno), *argv, ipc));
	send_ipc(ipc[1], CHDIR, path, NULL);
	send_ipc(ipc[1], ENV_ADD, "PWD", cwd);
	send_ipc_int(ipc[1], END_IPC, 0);
	exit(0);
}
