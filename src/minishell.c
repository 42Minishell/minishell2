// Created by Tom Jans on 27-02-21.

#include "minishell.h"

static void	process_input(t_state *state, char *input)
{
	t_token	*tokens;
	char	*exec_path;

	tokens = tokenizer(input, state->env->env);
	if (!tokens || !tokens->token)
	{
		tokenizer_list_free(tokens);
		return ;
	}
	exec_path = path_resolve(state->env, tokens->token);
	if (!exec_path)
	{
		if (errno != 0)
			printf("Error: %s\n", strerror(errno));
	}
	else
	{
		exec(state, exec_path, tokens);
		tokenizer_list_free(tokens);
		free(exec_path);
	}
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
