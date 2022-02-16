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

#include "config.h"
#include "tokenizer.h"
#include "libft.h"

static void	check_literal(char **c, t_literal_mode *mode)
{
	if (**c == '\'')
	{
		if (*mode == SINGLEQUOTE)
			*mode = DEFAULT;
		if (*mode == DEFAULT)
			*mode = SINGLEQUOTE;
		if (*mode == DOUBLEQUOTE)
			return ;
		(*c)++;
		check_literal(c, mode);
	}
	else if (**c == '"')
	{
		if (*mode == DOUBLEQUOTE)
			*mode = DEFAULT;
		if (*mode == DEFAULT)
			*mode = DOUBLEQUOTE;
		if (*mode == SINGLEQUOTE)
			return ;
		(*c)++;
		check_literal(c, mode);
	}
}

static	size_t copy_byte(char *in, char *dst, t_literal_mode mode)
{
	if(*in && (!is_special_character(*in) || mode))
	{
		*dst = *in;
		return (1);
	}
	return (0);
}

void	reallocate_string(char **s, size_t *buf_size)
{
	char	*new;

	new = malloc(*buf_size + TOK_ALLOC_BLK_SIZE);
	ft_memcpy(new, *s, *buf_size);
	*buf_size += TOK_ALLOC_BLK_SIZE;
	free(*s);
	*s = new;
}

char	*copy_str_until_special_char(char **in, struct s_state *state)
{
	size_t			pos;
	size_t			buf_size;
	size_t 			copy_ret;
	char			*s;
	t_literal_mode	literal_mode;

	(void)state;
	s = malloc(TOK_ALLOC_BLK_SIZE);
	pos = 0;
	literal_mode = DEFAULT;
	if (!s)
		return (NULL);
	while (**in)
	{
		if (pos == buf_size - 1)
			reallocate_string(&s, &buf_size);
		check_literal(in, &literal_mode);
		copy_ret = copy_byte(*in, s + pos, literal_mode);
		if (!copy_ret)
			break ;
		pos += copy_ret;
		(*in) += copy_ret;
	}
	return (s);
}
