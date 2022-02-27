/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parent_child_ipc.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 18:09:00 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/02/22 20:47:20 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "minishell.h"

t_pid_list	*g_pid;

// if get is true it gets the variable.
// if false it sets the variable.
pid_t	exit_status_child(pid_t new_status, _Bool get)
{
	static int	status;

	if (get == true)
		return (status);
	status = new_status;
	if (WIFEXITED(status) == true || WIFSIGNALED(status) == true)
		status = WEXITSTATUS(status);
	return (__INT_MAX__);
}

// Waits for all children and reaps them if neccessary.
void	wait_children(void)
{
	int		status;

	waitpid(-1, &status, 0);
	exit_status_child(status, false);
}
