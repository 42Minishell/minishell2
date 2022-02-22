/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parent_child_ipc.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 18:09:00 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/02/22 18:14:47 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "minishell.h"

// if get is true it gets the variable.
// if false it sets the variable.
pid_t	exit_status_child(pid_t new_status, _Bool get)
{
	static int	status;

	if (get == true)
		return (status);
	status = new_status;
	return (__INT_MAX__);
}

// Waits for all children and reaps them if neccessary.
void	wait_children(void)
{
	pid_t	ret;
	int		status;

	ret = __INT_MAX__;
	while (true)
	{
		ret = waitpid(-1, &status, WNOHANG);
		if (ret < 0)
			break ;
		exit_status_child(status, false);
	}
	return ;
}
