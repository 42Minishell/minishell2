/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 22:03:09 by tjans             #+#    #+#             */
/*   Updated: 2022/02/15 22:03:13 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

void	print_tokens(t_token *tokens)
{
	printf("Debug output for tokenizer\n");
	while (tokens)
	{
		if (tokens->type != executable && tokens->type != redirect_to_pipe)
			printf("\t");
		printf("Token: %s Type: %d ResType: %d pipe: %d:%d ipc: %d:%d\n",
			tokens->token, tokens->type, tokens->result_type,
			tokens->pipe_fd[0], tokens->pipe_fd[1],
			tokens->ipc_fd[0], tokens->ipc_fd[1]);
		tokens = tokens->next;
	}
	printf("\n");
}
