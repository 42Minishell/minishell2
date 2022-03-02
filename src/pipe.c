/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:13:56 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/03/02 19:49:17 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

int	pipes_init(t_token *token)
{
	while (token)
	{
		if (token->result_type == BUILTIN)
		{
			if (pipe(token->ipc_fd))
				return (1);
		}
		token = token->next;
	}
	return (0);
}
