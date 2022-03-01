/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_reader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 22:11:27 by tjans             #+#    #+#             */
/*   Updated: 2022/02/23 22:11:28 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/signal.h>
#include <unistd.h>
#include <fcntl.h>
#include "minishell.h"
#include "heredoc.h"
#include "tokenizer.h"

static void	return_error(int signal)
{
	(void)signal;
	exit(1);
}

static int	open_heredoc_fd(t_heredoc_list *heredoc)
{
	char	path[255];

	if (access("/tmp", W_OK) == 0)
		ft_strlcpy(path, "/tmp", 255);
	else
		getcwd(path, 255);
	ft_strlcat(path, "/", 255);
	ft_strlcat(path, heredoc->tmp_fn, 255);
	if (access(path, F_OK) == 0)
		unlink(path);
	ft_strlcpy(heredoc->fullpath, path, 255);
	return (open(path, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG));
}

static void	read_loop(int fd, char *delim)
{
	char	*line;
	char	*ret;
	char	nl;

	signal(SIGINT, &return_error);
	signal(SIGQUIT, &return_error);
	rl_clear_history();
	line = readline("heredoc> ");
	nl = '\n';
	while (line)
	{
		ret = ft_strnstr(line, delim, ft_strlen(delim));
		if (ret)
		{
			free(line);
			exit(0);
		}
		write(fd, line, ft_strlen(line));
		write(fd, &nl, 1);
		free(line);
		line = readline("heredoc> ");
	}
	exit(1);
}

int	heredoc_reader(t_heredoc_list *heredoc)
{
	int		fd;
	pid_t	pid;

	fd = open_heredoc_fd(heredoc);
	if (fd < 0)
		return (1);
	setup_nonint_signals();
	pid = fork_wrapper();
	if (!pid)
		read_loop(fd, heredoc->delim);
	else
	{
		close(fd);
		wait_children();
		free_pid_list();
	}
	setup_int_signals();
	return (exit_status_child(0, true));
}
