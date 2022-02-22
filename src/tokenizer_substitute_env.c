/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_substitute_env.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:34:57 by tjans             #+#    #+#             */
/*   Updated: 2022/02/16 16:35:00 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "config.h"
#include "tokenizer.h"
#include "minishell.h"
#include "libft.h"

static int	getkey(char *in, char *out)
{
	int	size;

	size = 0;
	while (*in && \
			((*in >= '0' && *in <= '9') || \
			(*in >= 'a' && *in <= 'z') || \
			(*in >= 'A' && *in <= 'Z') || \
			(*in == '_')))
	{
		out[size] = *in;
		size++;
		in++;
	}
	out[size] = 0;
	return (size);
}

static int	insert_exit_status_into_string(char **in, char **s, size_t *posbuf)
{
	char	*ret;
	size_t	vallen;

	ret = ft_itoa(exit_status_child(0, true));
	vallen = ft_strlen(ret);
	while (posbuf[BUF] - posbuf[POS] < vallen)
		reallocate_string(s, &posbuf[BUF]);
	strlcpy((*s) + posbuf[POS], ret, posbuf[BUF] - posbuf[POS]);
	posbuf[POS] += vallen;
	(*in) += 2;
	return (1);
}

int	insert_env_into_string(char **in, char **s, size_t *posbuf, \
	struct s_state *state)
{
	char	key[4096];
	int		keylen;
	char	*val;
	size_t	vallen;

	if (**in != '$' || !**in || *((*in) + 1) == ' ')
		return (0);
	if (*((*in) + 1) == '?')
		return (insert_exit_status_into_string(in, s, posbuf));
	keylen = getkey((*in) + 1, key);
	if (keylen)
	{
		(*in) += keylen + 1;
		val = bucket_get_value(state->env->env, key);
		if (val)
		{
			vallen = ft_strlen(val);
			while (posbuf[BUF] - posbuf[POS] < vallen)
				reallocate_string(s, &posbuf[BUF]);
			strlcpy((*s) + posbuf[POS], val, posbuf[BUF] - posbuf[POS]);
			posbuf[POS] += vallen;
		}
		return (1);
	}
	return (0);
}
