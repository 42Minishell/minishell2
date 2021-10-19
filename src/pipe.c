#include "minishell.h"
#include "io.h"
#include "tokenizer.h"

int	pipes_init(t_token *token)
{
	while (token)
	{
		if (token->type == redirect_to_pipe)
		{
			if (pipe(token->pipe_fd))
				return (1);
		}
		token = token->next;
	}
	return (0);
}

int pipes_destroy(t_token *token)
{
	while (token)
	{
		if (token->type == redirect_to_pipe)
		{
			close(token->pipe_fd[0]);
			close(token->pipe_fd[1]);
		}
		token = token->next;
	}
	return (0);
}
