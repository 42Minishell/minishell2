/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: tjans <tnjans@outlook.de>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 13:53:49 by tjans         #+#    #+#                 */
/*   Updated: 2022/02/23 16:29:02 by zgargasc      ########   odam.nl         */
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
		else if (*mode == DEFAULT)
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
		else if (*mode == DEFAULT)
			*mode = DOUBLEQUOTE;
		if (*mode == SINGLEQUOTE)
			return ;
		(*c)++;
		check_literal(c, mode);
	}
}

static size_t	copy_byte(char *in, char *dst, t_literal_mode mode)
{
	if (*in && (!is_special_character(*in) || mode))
	{
		*dst = *in;
		*(dst + 1) = 0;
		return (1);
	}
	dst++;
	*dst = 0;
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
	size_t			*posbuf;
	size_t			copy_ret;
	char			*s;
	t_literal_mode	literal_mode;

	s = malloc(TOK_ALLOC_BLK_SIZE);
	posbuf = (size_t[2]){0, TOK_ALLOC_BLK_SIZE};
	literal_mode = DEFAULT;
	if (!s)
		return (NULL);
	while (**in)
	{
		if (posbuf[POS] == posbuf[BUF] - 1)
			reallocate_string(&s, &posbuf[BUF]);
		check_literal(in, &literal_mode);
		if (literal_mode != SINGLEQUOTE && \
			insert_env_into_string(in, &s, posbuf, state))
			continue ;
		copy_ret = copy_byte(*in, s + posbuf[POS], literal_mode);
		if (!copy_ret)
			break ;
		posbuf[POS] += copy_ret;
		(*in) += copy_ret;
	}
	return (s);
}
