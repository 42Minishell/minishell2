// Created by Tom Jans on 01-03-21.

#include "minishell.h"

char	*prompt(t_state *state)
{
	char	*input;

	(void)state;
	setup_int_signals();
	input = readline("MS > ");
	if (!input)
	{
		printf("\n");
		exit(0);
	}
	if (*input)
		add_history(input);
	return (input);
}
