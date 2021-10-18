// Created by Tom Jans on 25-03-21.

#include <sys/wait.h>
#include "minishell.h"
#include "io.h"

static int	token_len(t_token *head)
{
	int	len;

	len = 1;
	head = head->next;
	while (head && head->type == non_special && head->token)
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

//TODO: MAKE BUILTINS FORK AND BEHAVE LIKE NOT BUUILT INS

void	exec_builtin(t_state *state, t_resolve_result *result, t_token *args)
{
	char	**argv;
	int		ret;
	int		stdout_copy;
	int		stdin_copy;

	stdout_copy = dup(1);
	stdin_copy = dup(0);
	if (!io_setup(args))
	{
		dup2(stdin_copy, 0);
		dup2(stdout_copy, 1);
		printf("Redirection failed: %s\n", strerror(errno));
		return ;
	}
	argv = populate_argv(args);
	ret = result->builtin(token_len(args), argv, state);
	state->ret = ret;
	free(argv);
	dup2(stdin_copy, 0);
	dup2(stdout_copy, 1);
	close(stdin_copy);
	close(stdout_copy);
}

static int is_there_a_pipe_somewhere_maybe(t_token *head)
{
	while (head)
	{
		head = head->next;
		if (head && head->type == redirect_to_pipe)
			return (1);
	}
	return (0);
}

static void	jump_to_next_pipe(t_token **head)
{
	t_token	*current;

	current = *head;
	current = current->next;
	while (current && current->type != redirect_to_pipe && current->next)
		current = current->next;
	*head = current;
}

/**
 * @brief TOFIX:
 * 1. check pipe
 * 2. if pipe dup io
 * 3. fork, open pipe
 * 4. in child transform into exec token; continue normal logic
 * 5. in parent continue with parent exec token
 */
void	exec(t_state *state, t_token *cur_token, int pipe_fd)
{
	char			**argv;
	int				filedes[2];
	int				should_pipe = is_there_a_pipe_somewhere_maybe(cur_token);
	int status;

	if (pipe(filedes))
	{
		printf("kaputt.\n");
		exit(1);
	}
	if (pipe_fd != -1)
		dup2(pipe_fd, 0);
	g_child_pid = fork();
	if (!g_child_pid)
	{
		if (!io_setup(cur_token))
		{
			printf("Redirection failed: %s\n", strerror(errno));
			exit(1);
		}
		if (should_pipe)
		{
			dup2(filedes[1], 1);
			jump_to_next_pipe(&cur_token);
			exec(state, cur_token, filedes[0]);
		}
		argv = populate_argv(cur_token);
		execve(cur_token->result.path, argv, state->env->envp);
	}
}
