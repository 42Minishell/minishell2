// Created by Tom Jans on 01-03-21.

#include "minishell.h"

char	*prompt(t_state *state)
{
	char	*ret;

	printf("MS > ");
	if (fd_readline(state->sin, &ret) == -1)
		return (NULL);
	if (ft_strncmp(ret, "exit", 5) == 0)
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}
