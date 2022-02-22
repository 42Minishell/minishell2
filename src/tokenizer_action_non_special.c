/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_action_non_special.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:58:40 by tjans             #+#    #+#             */
/*   Updated: 2022/02/16 11:58:41 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"

int	lexer_action_non_special(t_token **dst, char **in, \
	struct s_state *state)
{
	t_token	*token;

	token = create_token(dst);
	if (!token)
		return (1);
	token->token = copy_str_until_special_char(in, state);
	if (!token->token)
		return (1);
	return (0);
}
