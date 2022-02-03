/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:56 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:15:12 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell.h"
#include "io.h"
#include "tokenizer.h"

t_token *find_pipe(t_token *token)
{
    t_token *next;

    next = token->next;
    while (next)
    {
        if (next->type == redirect_to_pipe)
            return (next);
        if (next->type == executable)
            return (NULL);
        next = next->next;
    }
    return (NULL);
}

int	pipes_init(t_token *token)
{
    t_token *next_pipe;

	while (token)
	{
        next_pipe = find_pipe(token);
		if (token->type == redirect_to_pipe && token->result_type != BUILTIN)
		{
			if (pipe(token->pipe_fd))
				return (1);
		}
		else if (next_pipe && next_pipe->type == redirect_to_pipe)
		{
			token->pipe_fd[1] = open("/dev/null", O_WRONLY);
			if (token->pipe_fd[1] < 0)
				return (1);
		}
		token = token->next;
	}
	return (0);
}

int	pipes_destroy(t_token *token)
{
	while (token)
	{
		if (token->type == redirect_to_pipe && token->result_type != BUILTIN)
		{
			close(token->pipe_fd[0]);
			close(token->pipe_fd[1]);
		}
		else if (token->type == redirect_to_pipe)
			close(token->pipe_fd[1]);
		token = token->next;
	}
	return (0);
}
