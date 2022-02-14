/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals_noninteractive.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:14:05 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:15:00 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

static void	handle_ctrlc(int signal)
{
	(void)signal;
	kill(g_child_pid, SIGINT);
}

static void	handle_backslash(int signal)
{
	(void)signal;
	kill(g_child_pid, SIGTERM);
}

static void	handle_sigchld(int signal)
{
	(void)signal;
}

void	setup_nonint_signals(void)
{
	struct sigaction	act_sigint;
	struct sigaction	act_sigquit;
	struct sigaction	act_sigchld;

	act_sigint.sa_handler = handle_ctrlc;
	act_sigint.sa_flags = 0;
	act_sigchld.sa_handler = handle_sigchld;
	act_sigchld.sa_flags = 0;
	act_sigquit.sa_handler = handle_backslash;
	sigemptyset(&act_sigint.sa_mask);
	sigemptyset(&act_sigquit.sa_mask);
	sigemptyset(&act_sigchld.sa_mask);
	act_sigquit.sa_flags = 0;
	sigaction(SIGINT, &act_sigint, NULL);
	sigaction(SIGQUIT, &act_sigquit, NULL);
	sigaction(SIGCHLD, &act_sigchld, NULL);
}
