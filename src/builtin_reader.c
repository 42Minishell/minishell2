/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:17:15 by tjans             #+#    #+#             */
/*   Updated: 2022/02/15 11:17:16 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "builtins.h"

int	builtin_reader(int argc, char **argv, t_state *state, int ipc[2])
{
	t_fdstream	*stdin_fds;
	char		*line;
	char		*res;
	char		nl;

	(void)argc;
	(void)state;
	(void)ipc;
	nl = '\n';
	stdin_fds = fd_openfd(STDIN_FILENO);
	while (fd_readline(stdin_fds, &line) >= 0)
	{
		res = ft_strnstr(line, argv[1], ft_strlen(line));
		if (res)
			break ;
		write(STDOUT_FILENO, line, ft_strlen(line));
		write(STDOUT_FILENO, &nl, 1);
		free(line);
	}
	fd_close(stdin_fds);
	return (0);
}
