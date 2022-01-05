/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:51 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/19 12:40:39 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 27-02-21.

#include <sys/wait.h>
#include "minishell.h"

pid_t	g_child_pid;

static void	jump_to_next_exec(t_token **head)
{
	t_token	*current;

	current = *head;
	current = current->next;
	while (current && current->type != executable && current->next)
		current = current->next;
	*head = current;
}

static int	count_exec(t_token *head)
{
	int	i;

	i = 0;
	while (head)
	{
		if (head->type == executable || head->type == redirect_to_pipe)
			i++;
		head = head->next;
	}
	return (i);
}

void	save_close_pipes(t_token *token)
{
	while (token->next && token->next->type != redirect_to_pipe)
		token = token->next;
	if (token->next && token->next->type == redirect_to_pipe && token->next->result_type != BUILTIN)
	{
		printf("closed %d: %d %d\n", token->pid, \
			token->next->pipe_fd[0], \
			token->next->pipe_fd[1]);
		if (close(token->next->pipe_fd[1]) == -1)
			ft_error("closing fd went wrong", 22);
		if (token->result_type == BUILTIN)
		{
			dup2(token->pipe_fd[0], 0);
			dup2(token->pipe_fd[1], 1);
		}
		else
		{
			if (close(token->next->pipe_fd[0]) == -1)
				ft_error("closing fd went wrong", 22);
		}
	}
}

static void	wait_for_children(t_token *head)
{
	int		died;
	t_token	*token;
	int		status;
	int		total;

	died = 0;
	total = count_exec(head);
    status = 0;
	while (died < total)
	{
		token = head;
		while (token)
		{
			if (token->type == executable || token->type == redirect_to_pipe)
			{
				if (token->result_type != BUILTIN)
					waitpid(token->pid, &status, 0);
				if ((token->result_type == BUILTIN && token->pid == -1) || WIFEXITED(status) || WIFSIGNALED(status))
				{
					save_close_pipes(token);
					died++;
					token->type = non_special;
				}
			}
			token = token->next;
		}
	}
}

static int	process_input_loop(t_state *state, t_token *tokens)
{
	if (tokens->type != executable || tokens->result_type == NOTFOUND)
		return (0);
	exec(state, tokens);
	jump_to_next_exec(&tokens);
	return (process_input_loop(state, tokens));
}

static void	process_input(t_state *state, char *input)
{
	t_token					*tokens;

	tokens = tokenizer(input, state);
	if (!tokens || !tokens->token)
	{
		tokenizer_list_free(tokens);
		return ;
	}
	path_resolve_token_list(state->env, tokens);
	pipes_init(tokens);
	setup_nonint_signals();
	process_input_loop(state, tokens);
	wait_for_children(tokens);
	tokenizer_list_free(tokens);
	setup_int_signals();
}

static void	loop(t_state *state)
{
	char	*input;

	while (1)
	{
		errno = 0;
		input = prompt(state);
		if (!input)
			break ;
		process_input(state, input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_state	state;

	setbuf(stdout, NULL);
	(void)argc;
	setup_int_signals();
	state_init(&state, argv, envp);
	loop(&state);
	state_free(&state);
	return (0);
}
