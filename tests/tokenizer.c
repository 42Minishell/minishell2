// Created by Tom Jans on 12-03-21.

#include <wait.h>
#include "minishell.h"
#include "tokenizer.h"

static void	eexec(t_state *state, char *path)
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

int main(int argc, char **argv)
{
	char *test;
	t_token *tk;
	t_token *tkp;

	if (argc < 2)
		return (1);
	t_state state;
	state_init(&state, argv);

	eexec(&state, "/usr/bin/env");
	test = ft_strdup(argv[1]);
	printf("\nInput: %s\n", test);
	//res_env(&test, state.env->env);
	//printf("res_env: %s\n", test);
	tk = tokenizer(test, state.env->env);
	while (tk)
	{
		printf("token: %s\n", tk->token);
		tkp = tk;
		tk = tk->next;
		if (tkp->token)
			free(tkp->token);
		free(tkp);
	}
	state_free(&state);
	return (0);
}