// Created by Tom Jans on 01-03-21.

#include "minishell.h"

char	*prompt(t_state *state)
{
	char	*input;

	(void)state;
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
