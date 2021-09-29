#include <termios.h>
#include "minishell.h"

static void	handle_backslash(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_ctrlc(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

static void	disable_special_key_echo(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

void	setup_int_signals(void)
{
	signal(SIGQUIT, handle_backslash);
	signal(SIGINT, handle_ctrlc);
	disable_special_key_echo();
}