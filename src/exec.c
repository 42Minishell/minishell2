// Created by Tom Jans on 25-03-21.

#include <wait.h>
#include "minishell.h"

static int	token_len(t_token *head)
{
	int	len;

	len = 0;
	while (head)
	{
		head = head->next;
		len++;
	}
	return (len);
}

static char	**populate_argv(t_token *head)
{
	char	**argv;
	int		len;
	int		i;

	len = token_len(head);
	argv = ft_calloc(len + 1, sizeof(char *));
	i = 0;
	while (i < len)
	{
		argv[i] = head->token;
		head = head->next;
		i++;
	}
	return (argv);
}

void	exec(t_state *state, char *path, t_token *args)
{
	pid_t	child;
	char	**argv;
	int		status;

	child = fork();
	if (!child)
	{
		argv = populate_argv(args);
		execve(path, argv, state->env->envp);
	}
	while (waitpid(child, &status, 0))
	{
		if (WIFEXITED(status) || WIFSIGNALED(status))
			break ;
	}
}