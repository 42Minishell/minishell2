/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fork_wrapper_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/23 15:26:00 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/02/23 16:31:47 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pid_list	*make_node(void)
{
	t_pid_list	*new;

	new = NULL;
	new = (t_pid_list *)malloc(sizeof(t_pid_list));
	if (!new)
		ft_error("pid list malloc error", 22);
	new->next = NULL;
	new->pid = fork();
	return (new);
}

void	free_pid_list(void)
{
	t_pid_list	*current;
	t_pid_list	*temp;

	current = NULL;
	temp = NULL;
	if (g_pid == NULL)
		return ;
	current = g_pid;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp);
	}
	g_pid = NULL;
	return ;
}

pid_t	fork_wrapper(void)
{
	t_pid_list	*current;

	current = NULL;
	if (g_pid == NULL)
	{
		g_pid = make_node();
		current = g_pid;
	}
	else
	{
		current = g_pid;
		while (current->next)
			current = current->next;
		current->next = make_node();
		current = current->next;
	}
	return (current->pid);
}
