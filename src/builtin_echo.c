/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:33 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:13:34 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// Created by Tom Jans on 28-03-21.

#include "builtins.h"

static int	check_opt(char *str)
{
	if (ft_strncmp("-n", str, 3) == 0)
		return (0);
	return (1);
}

int	builtin_echo(int argc, char **argv, t_state *state, int ipc[2])
{
	int	i;
	int	print_newline;

	(void)state;
	(void)ipc;
	if (argc < 2)
		exit(0);
	print_newline = check_opt(argv[1]);
	i = 2 - print_newline;
	while (i < argc)
	{
		printf("%s", argv[i]);
		if (i + 1 < argc)
			printf(" ");
		i++;
	}
	if (print_newline)
		printf("\n");
	exit(0);
}
