/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:51 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:22:43 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 27-02-21.

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

static void	wait_for_children(t_state *state, t_token *head)
{
	int		died;
	t_token	*token;
	int		status;
	int		total;

	died = 0;
	total = count_exec(head);
	while (died < total)
	{
		token = head;
		while (token)
		{
			if (token->type == executable || token->type == redirect_to_pipe)
			{
				waitpid(token->pid, &status, 0);
				if (WIFEXITED(status) || WIFSIGNALED(status))
				{
					if (token->next->type == redirect_to_pipe)
					{
						printf("closed %d: %d %d\n", token->pid, \
								token->next->pipe_fd[0], \
								token->next->pipe_fd[1]);
						if (close(token->next->pipe_fd[0]) == -1 \
							|| close(token->next->pipe_fd[1]) == -1)
							ft_error("closing fd went wrong", 22);
					}
					died++;
					token->type = non_special;
				}
			}
			token = token->next;
		}
	}
}

static void	jump_to_next_pipe(t_token **head)
{
	t_token	*current;

	current = *head;
	current = current->next;
	while (current && current->type != redirect_to_pipe && current->next)
		current = current->next;
	*head = current;
}

static int	process_input_loop(t_state *state, t_token *tokens)
{
	int	pipe[2];

	pipe[0] = -1;
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
	wait_for_children(state, tokens);
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
