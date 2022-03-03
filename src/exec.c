/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:12:26 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/03/02 20:00:35 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 25-03-21.

#include "minishell.h"
#include "io.h"
#include "ipc.h"

static t_token	*get_next_pipe_token(t_token *head)
{
	while (head)
	{
		if (head->type == redirect_to_pipe)
			return (head);
		head = head->next;
	}
	return (NULL);
}

void	io_setup_child(t_token *cur_token, t_token *next_token)
{
	if (!io_setup(cur_token))
	{
		printf("Redirection failed: %s\n", strerror(errno));
		if (cur_token->result_type == BUILTIN)
			send_ipc_int(cur_token->ipc_fd[1], END_IPC, 0);
		exit(1);
	}
	if (cur_token->type == redirect_to_pipe)
	{
		close(cur_token->pipe_fd[1]);
		if (dup2(cur_token->pipe_fd[0], 0) == -1)
			ft_error("exec error", 11);
		close(cur_token->pipe_fd[0]);
	}
	if (next_token)
	{
		close(next_token->pipe_fd[0]);
		if (dup2(next_token->pipe_fd[1], 1) == -1)
			ft_error("exec error", 11);
		close(next_token->pipe_fd[1]);
	}
}

void	exec(t_state *state, t_token *cur_token)
{
	t_token			*next_token;

	while (cur_token &&
			cur_token->type != executable && cur_token->type != redirect_to_pipe)
		cur_token = cur_token->next;
	if (!cur_token)
		return ;
	next_token = get_next_pipe_token(cur_token->next);
	if (next_token && pipe(next_token->pipe_fd))
		ft_error("pipe baaaad\n", 13);
	cur_token->pid = fork_wrapper();
	if (cur_token->pid == -1)
		ft_error("fork went wrong", 16);
	if (!cur_token->pid)
		exec_child(cur_token, state, next_token);
	else if (cur_token->type == redirect_to_pipe)
	{
		close(cur_token->pipe_fd[0]);
		close(cur_token->pipe_fd[1]);
	}
	if (next_token)
		exec(state, next_token);
}
