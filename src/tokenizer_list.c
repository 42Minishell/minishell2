/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 11:32:54 by tjans             #+#    #+#             */
/*   Updated: 2022/02/16 11:32:55 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"

t_token	*token_create_empty(t_token *next, t_token *prev)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = next;
	token->prev = prev;
	return (token);
}

t_token	*create_token(t_token **dst)
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
