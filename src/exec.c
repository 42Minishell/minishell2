/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:12:26 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/01/05 15:00:30 by zgargasc      ########   odam.nl         */
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

/**
 * @brief TOFIX:
 * 1. check pipe
 * 2. if pipe dup io
 * 3. fork, open pipe
 * 4. in child transform into exec token; continue normal logic
 * 5. in parent continue with parent exec token
 */

void	io_setup_child(t_token *cur_token, t_token *pipe)
{
	if (!io_setup(cur_token))
	{
		printf("Redirection failed: %s\n", strerror(errno));
		exit(1);
	}
	if (pipe && pipe->result_type != BUILTIN)
	{
		if (dup2(pipe->pipe_fd[1], 1) == -1)
			ft_error("exec error (pipe and cur)", 25);
        if (cur_token->result_type != BUILTIN)
        {
            close(pipe->pipe_fd[0]);
            close(pipe->pipe_fd[1]);
        }
	}
	else if (pipe) {
        if (dup2(cur_token->pipe_fd[1], 1) == -1)
            ft_error("exec error (devnull)", 20);
    }
	if (cur_token->type == redirect_to_pipe && \
			cur_token->result_type != BUILTIN)
	{
		if (dup2(cur_token->pipe_fd[0], 0) == -1)
			ft_error("exec error (redir to)", 21);
        close(cur_token->pipe_fd[0]);
        close(cur_token->pipe_fd[1]);
	}
}

void	exec_builtin_clean(t_token *builtin)
{
		dup2(builtin->pipe_fd[0], 0);
		dup2(builtin->pipe_fd[1], 1);
		close(builtin->pipe_fd[0]);
		close(builtin->pipe_fd[1]);
}

void	exec_builtin(t_state *state, \
		t_resolve_result *result, t_token *args, \
			t_token *pipe)
{
	char	**argv;
	int		ret;

	args->pipe_fd[1] = dup(1);
	args->pipe_fd[0] = dup(0);
	if (args->pipe_fd[1] == -1 || args->pipe_fd[0] == -1)
		ft_error("fd dup went wrong", 18);
	io_setup_child(args, pipe);
	argv = populate_argv(args);
	ret = result->builtin(token_len(args), argv, state);
	state->ret = ret;
	free(argv);
	exec_builtin_clean(args);
}

void	exec(t_state *state, t_token *cur_token)
{
	t_token			*pipe;
    char			**argv;

    pipe = get_next_pipe_token(cur_token->next);
	if (cur_token->result_type == BUILTIN)
	{
        if (pipe)
            exec(state, pipe);
		exec_builtin(state, &cur_token->result, cur_token, pipe);
		cur_token->pid = -1;
		return ;
	}
	cur_token->pid = fork();
	if (cur_token->pid == -1)
		ft_error("fork went wrong", 16);
	g_child_pid = cur_token->pid;
	if (!g_child_pid)
    {
        io_setup_child(cur_token, pipe);
        argv = populate_argv(cur_token);
        execve(cur_token->result.path, argv, state->env->envp);
    }
    if (cur_token->result_type != BUILTIN && pipe)
        exec(state, pipe);
}
