/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_action_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:27:33 by tjans             #+#    #+#             */
/*   Updated: 2022/02/16 14:27:34 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int	prev_exec(t_token **head)
{
	t_token	*iterator;

	iterator = *head;
	while (iterator)
	{
		if (iterator->type == non_special || iterator->type == redirect_to_pipe
			|| iterator->type == executable)
			return (1);
		iterator = iterator->prev;
	}
	return (0);
}

int	lexer_action_pipe(t_token **dst, char **in, \
	struct s_state *state)
{
	t_token	*token;

	if (!*dst || !prev_exec(dst))
		return (1);
	token = create_token(dst);
	if (!token)
		return (1);
	(*in)++;
	lexer_action_whitespace(NULL, in, state);
	if (!**in || is_special_character(**in))
		return (1);
	token->token = copy_str_until_special_char(in, state);
	token->type = redirect_to_pipe;
	return (0);
}
