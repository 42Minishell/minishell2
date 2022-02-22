/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:51 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/02/22 17:51:10 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 27-02-21.

#include <sys/wait.h>
#include "minishell.h"
#include "ipc.h"
#include "io.h"

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

// if get is true it gets the variable.
// if false it sets the variable.
pid_t		exit_status_child(pid_t new_status, _Bool get)
{
	static int status;

	if (get == true)
		return (status);
	status = new_status;
	return (__INT_MAX__);
}

// Waits for all children and reaps them if neccessary.
static void	wait_children(void)
{
	pid_t ret;
	int status;

	ret = __INT_MAX__;
	while (true)
	{
		ret = waitpid(-1, &status, WNOHANG);
		if (ret < 0)
			break;
		exit_status_child(status, false);
	}
	return ;
}

static void	process_input(t_state *state, char *input)
{
	t_token		*tokens;

	tokens = tokenizer(input, state);
	if (!tokens || !tokens->token)
	{
		tokenizer_list_free(tokens);
		return ;
	}
	if (path_resolve_token_list(state->env, tokens))
		return ((void)printf("Error: %s\n", strerror(errno)));
	tokens = replace_delims_with_pipes(tokens);
	pipes_init(tokens);
	setup_nonint_signals();
	exec(state, tokens);
	wait_children();
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
