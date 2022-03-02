/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:51 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/03/02 19:54:33 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 27-02-21.

#include <sys/wait.h>
#include "minishell.h"
#include "ipc.h"
#include "heredoc.h"

static void	set_err_and_prt(char *s)
{
	exit_status_child(127, false, false);
	printf("Error: %s\n", s);
}

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
	t_token		*tokens;

	tokens = tokenizer(input, state);
	if (!tokens || !tokens->token)
	{
		free_token_list(tokens);
		return ;
	}
	if (path_resolve_token_list(state->env, tokens))
		set_err_and_prt("Command not found.");
	if (process_heredocs(tokens) == 0)
	{
		pipes_init(tokens);
		setup_nonint_signals();
		g_pid = NULL;
		exec(state, tokens);
		start_builtin_ipc(state, tokens);
		wait_children();
		free_pid_list();
	}
	else
		set_err_and_prt("Heredoc aborted.\n");
	free_token_list(tokens);
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

	(void)argc;
	setup_int_signals();
	state_init(&state, argv, envp);
	loop(&state);
	state_free(&state);
	return (0);
}
