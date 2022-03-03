/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parent_child_ipc.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/22 18:09:00 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/03/02 21:07:57 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "minishell.h"

t_pid_list	*g_pid;

// if get is true it gets the variable.
// if false it sets the variable.
pid_t	exit_status_child(pid_t new_status, _Bool get, _Bool non_stat)
{
	static int	status;

	if (non_stat == true)
	{
		status = (int)new_status;
		return (__INT_MAX__);
	}
	if (get == true)
		return (status);
	status = new_status;
	if (WIFEXITED(status) == true || WIFSIGNALED(status) == true)
		status = WEXITSTATUS(status);
	return (__INT_MAX__);
}

/// Waits for all children and reaps them if neccessary.
void	wait_children(void)
{
	int				status;
	t_pid_list		*current;

	current = g_pid;
	if (!current)
		return ;
	while (current->next)
		current = current->next;
	while (waitpid(-1, &status, 0) >= 0)
		continue ;
	exit_status_child(status, false, false);
}
