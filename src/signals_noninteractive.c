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
	kill(0, SIGINT);
}

static void	handle_backslash(int signal)
{
	(void)signal;
	kill(0, SIGTERM);
}

void	setup_nonint_signals(void)
{
	struct sigaction	act_sigint;
	struct sigaction	act_sigquit;

	act_sigint.sa_handler = handle_ctrlc;
	act_sigint.sa_flags = 0;
	act_sigquit.sa_handler = handle_backslash;
	sigemptyset(&act_sigint.sa_mask);
	sigemptyset(&act_sigquit.sa_mask);
	act_sigquit.sa_flags = 0;
	sigaction(SIGINT, &act_sigint, NULL);
	sigaction(SIGQUIT, &act_sigquit, NULL);
}
