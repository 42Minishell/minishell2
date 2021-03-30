// Created by Tom Jans on 27-02-21.

#include "minishell.h"

static void	jump_to_next_exec(t_token **head)
{
	t_token *current;

	current = *head;
	while (current->type != executable && current->next)
		current = current->next;
	*head = current;
}

static void	process_input(t_state *state, char *input)
{
	t_token	*tokens;
	t_token	*tokens_orig;
	char	*exec_path;

	tokens = tokenizer(input, state->env->env);
	tokens_orig = tokens;
	if (!tokens || !tokens->token)
	{
		tokenizer_list_free(tokens);
		return ;
	}
	while (tokens && tokens->type == executable)
	{
		exec_path = path_resolve(state->env, tokens->token);
		if (!exec_path)
		{
			if (errno != 0)
				printf("Error: %s\n", strerror(errno));
			break ;
		}
		else
		{
			exec(state, exec_path, tokens);
			free(exec_path);
			tokens = tokens->next;
			jump_to_next_exec(&tokens);
		}
	}
	tokenizer_list_free(tokens_orig);
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

int	main(int argc, char **argv)
{
	t_state	state;

	setbuf(stdout, NULL);
	(void)argc;
	state_init(&state, argv);
	loop(&state);
	state_free(&state);
	return (0);
}
