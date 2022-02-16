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

static t_token	*create_token(t_token **dst)
{
	if (!*dst)
	{
		*dst = token_create_empty(NULL, NULL);
		if (!*dst)
			return (NULL);
	}
	else
	{
		(*dst)->next = token_create_empty(NULL, *dst);
		if (!(*dst)->next)
			return (NULL);
	}
	if (!(*dst)->next)
		return (*dst);
	return ((*dst)->next);
}

static size_t	strlen_until_special_char(char *in)
{
	size_t	i;

	i = 0;
	while (in[i] && !is_special_character(in[i]))
		i++;
	return (i);
}

int	lexer_action_non_special(t_token **dst, char **in)
{
	t_token	*token;
	size_t	len;

	token = create_token(dst);
	if (!token)
		return (1);
	len = strlen_until_special_char(*in);
	token->token = malloc(len + 1 * sizeof(char));
	if (!token->token)
		return (1);
	ft_strlcpy(token->token, *in, len + 1);
	*in += len;
	return (0);
}
