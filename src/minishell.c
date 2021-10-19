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

static void	wait_for_child(t_state *state)
{
	int	status;

	while (waitpid(g_child_pid, &status, 0)
		&& !(WIFEXITED(status) || WIFSIGNALED(status)))
		(void)status;
	state->ret = WEXITSTATUS(status);
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

// FIXME: FIXME

static int process_input_loop(t_state *state, t_token *tokens)
{
	int pipe[2];

	pipe[0] = -1;
	if (tokens->type != executable)
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
	wait_for_child(state);
	setup_int_signals();
	tokenizer_list_free(tokens);
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
