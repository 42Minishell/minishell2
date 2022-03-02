/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/02 19:58:01 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/03/02 20:03:47 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_len(t_token *head)
{
	int	len;

	len = 1;
	head = head->next;
	while (head && head->type == non_special && head->token)
	{
		if (!*head->token)
		{
			head = head->next;
			continue ;
		}
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
	if (!argv)
		ft_error("calloc went wrong", 18);
	i = 0;
	while (i < len)
	{
		if (head && !*head->token)
		{
			head = head->next;
			continue ;
		}
		argv[i] = head->token;
		head = head->next;
		i++;
	}
	return (argv);
}

void	exec_child(t_token *cur_token, t_state *state, t_token *pipe_)
{
	char			**argv;

	io_setup_child(cur_token, pipe_);
	argv = populate_argv(cur_token);
	if (cur_token->result_type == BUILTIN)
		exec_builtin(state, cur_token, argv);
	else if (cur_token->result_type != NOTFOUND)
		execve(cur_token->result.path, argv, state->env->envp);
	exit(1);
}
