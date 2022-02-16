/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 13:53:49 by tjans             #+#    #+#             */
/*   Updated: 2022/02/16 13:53:50 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"
#include "libft.h"

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

static size_t	strlen_until_special_char(char *in)
{
	size_t	i;

	i = 0;
	while (in[i] && !is_special_character(in[i]))
		i++;
	return (i);
}

char	*copy_str_until_special_char(char *in, size_t *chars_copied)
{
	size_t	len;
	char	*s;

	len = strlen_until_special_char(in);
	s = malloc(len + 1 + sizeof(char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, in, len + 1);
	if (chars_copied)
		*chars_copied = len;
	return (s);
}
