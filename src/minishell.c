// Created by Tom Jans on 27-02-21.
#include <sys/wait.h>
#include "minishell.h"

static void	exec(t_state *state, char *path)
{
	pid_t	child;
	char	**argv;
	int		status;

	child = fork();
	if (!child)
	{
		argv = ft_calloc(2, sizeof(char *));
		argv[0] = path;
		execve(path, argv, state->env->envp);
	}
	while (waitpid(child, &status, 0))
	{
		if (WIFEXITED(status) || WIFSIGNALED(status))
			break ;
	}
}

static void	loop(t_state *state)
{
	char					*input;
	t_resolve_result		result;
	t_resolve_result_type	res_type;

	while (1)
	{
		errno = 0;
		input = prompt(state);
		if (!input)
			break ;
		res_type = path_resolve(state->env, input, &result);
		if (res_type == NOTFOUND)
		{
			if (errno != 0)
				printf("Error: %s\n", strerror(errno));
		}
		else if (res_type == BUILTIN)
			result.builtin(0, NULL, state);
		else
		{
			exec(state, result.path);
			free(result.path);
		}
		free(input);
	}
}

int	main(int argc, char **argv)
{
	t_state	state;

	(void)argc;
	state_init(&state, argv);
	loop(&state);
	state_free(&state);
	return (0);
}
