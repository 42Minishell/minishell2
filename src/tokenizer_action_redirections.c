/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_action_redirections.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:52:33 by tjans             #+#    #+#             */
/*   Updated: 2022/02/16 13:52:34 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"

int	lexer_action_redirection_right(t_token **dst, char **in, \
	struct s_state *state)
{
	t_token	*token;
	int		is_double;

	(*in)++;
	is_double = (**in == '>');
	(*in) += is_double;
	lexer_action_whitespace(NULL, in, state);
	if (!**in || is_special_character(**in))
		return (1);
	token = create_token(dst);
	if (!token)
		return (1);
	token->token = copy_str_until_special_char(in, state);
	if (is_double)
		token->type = redirect_to_append;
	else
		token->type = redirect_to_overwrite;
	return (0);
}

int	lexer_action_redirection_left(t_token **dst, char **in, \
	struct s_state *state)
{
	t_token	*token;
	int		is_double;

	(*in)++;
	is_double = (**in == '<');
	(*in) += is_double;
	lexer_action_whitespace(NULL, in, state);
	if (!**in || is_special_character(**in))
		return (1);
	token = create_token(dst);
	if (!token)
		return (1);
	token->token = copy_str_until_special_char(in, state);
	if (is_double)
		token->type = read_until_delimiter;
	else
		token->type = redirect_from_file;
	return (0);
}
