// Created by Tom Jans on 01-03-21.

#include "minishell.h"

char	*prompt(t_state *state)
{
	char	*ret;

	write(1, "MS > ", 6);
	if (fd_readline(state->sin, &ret) == -1)
		return (NULL);
	return (ret);
}
