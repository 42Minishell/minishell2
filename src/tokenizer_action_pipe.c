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

int	lexer_action_pipe(t_token **dst, char **in)
{
	t_token	*token;
	size_t	len;

	if (!*dst)
		return (1);
	token = create_token(dst);
	if (!token)
		return (1);
	(*in)++;
	lexer_action_whitespace(NULL, in);
	if (!**in || is_special_character(**in))
		return (1);
	token->token = copy_str_until_special_char(*in, &len);
	token->type = redirect_to_pipe;
	(*in) += len;
	return (0);
}
