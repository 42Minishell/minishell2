/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:12:26 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/02/24 17:15:30 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 25-03-21.

#include "minishell.h"
#include "io.h"

static int	token_len(t_token *head)
{
	int	len;

	len = 1;
	head = head->next;
	while (head && head->type == non_special && head->token)
	{
		head = head->next;
		len++;
	}
	return (len);
}

static char	**populate_argv(t_token *head)
{
	char	**argv;
	int		len;
	int		i;

	len = token_len(head);
	argv = ft_calloc(len + 1, sizeof(char *));
	if (!argv)
		ft_error("calloc went wrong", 18);
	i = 0;
	while (i < len)
	{
		argv[i] = head->token;
		head = head->next;
		i++;
	}
	return (argv);
}

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

void	io_setup_child(t_token *cur_token, t_token *pipe)
{
	if (!io_setup(cur_token))
	{
		printf("Redirection failed: %s\n", strerror(errno));
		exit(1);
	}
	if (pipe)
	{
		close(pipe->pipe_fd[0]);
		if (dup2(pipe->pipe_fd[1], 1) == -1)
			ft_error("exec error", 11);
		close(pipe->pipe_fd[1]);
	}
	if (cur_token->type == redirect_to_pipe)
	{
		close(cur_token->pipe_fd[1]);
		if (dup2(cur_token->pipe_fd[0], 0) == -1)
			ft_error("exec error", 11);
		close(cur_token->pipe_fd[0]);
	}
}

void	exec(t_state *state, t_token *cur_token)
{
	t_token			*pipe;
	char			**argv;

	pipe = get_next_pipe_token(cur_token->next);
	cur_token->pid = fork_wrapper();
	if (cur_token->pid == -1)
		ft_error("fork went wrong", 16);
	if (!cur_token->pid)
	{
		io_setup_child(cur_token, pipe);
		argv = populate_argv(cur_token);
		if (cur_token->result_type == BUILTIN)
			exec_builtin(state, cur_token, argv);
		else
			execve(cur_token->result.path, argv, state->env->envp);
		exit(1);
	}
	else if (cur_token->type == redirect_to_pipe)
	{
		close(cur_token->pipe_fd[0]);
		close(cur_token->pipe_fd[1]);
	}
	if (pipe)
		exec(state, pipe);
}
