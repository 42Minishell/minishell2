/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:51 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/01/05 15:01:06 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 27-02-21.

#include <sys/wait.h>
#include "minishell.h"
#include "ipc.h"

pid_t	g_child_pid;

static void	start_builtin_ipc(t_state *state, t_token *tokens)
{
	while (tokens)
	{
		if (tokens->result_type == BUILTIN)
		{
			receive_and_process_ipc(tokens->ipc_fd[0], state);
			close(tokens->ipc_fd[0]);
			close(tokens->ipc_fd[1]);
		}
		tokens = tokens->next;
	}
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
	exec(state, tokens);
	pipes_destroy(tokens);
	start_builtin_ipc(state, tokens);
	while (wait(&state->ret) > 0)
	{
	}
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
