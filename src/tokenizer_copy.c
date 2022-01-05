/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_copy.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/05 14:59:21 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/01/05 14:59:23 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

static int
	check_if_token_ended(char *src, size_t src_pos, char literal, size_t len)
{
	return (
		src_pos < len
		&& src[src_pos]
		&& !(!literal && iswhitespace(src[src_pos]))
		&& tokenizer_identify(src + src_pos) == non_special);
}

static void
	set_vars_to_zero(size_t *a, size_t *b, char *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}

static int
	check_literal_end(char *src, size_t src_pos)
{
	return (iswhitespace(src[src_pos + 1])
		|| tokenizer_identify(src + src_pos + 1) != non_special);
}

size_t	copy_str_to_token(char *dst, char *src, size_t len, t_tokens *type)
{
	size_t	dst_pos;
	size_t	src_pos;
	char	literal;

	set_vars_to_zero(&dst_pos, &src_pos, &literal);
	while (check_if_token_ended(src, src_pos, literal, len))
	{
		if (src[src_pos] == '\'' || src[src_pos] == '\"')
		{
			if (literal == src[src_pos])
			{
				literal = 0;
				if (check_literal_end(src, src_pos))
					return (src_pos + 1);
			}
			else if (!literal)
				literal = src[src_pos];
			src_pos++;
		}
		dst[dst_pos] = src[src_pos];
		dst_pos++;
		src_pos++;
	}
	*type = tokenizer_identify(src + src_pos);
	return (src_pos + 1);
}
