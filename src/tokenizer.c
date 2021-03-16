/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_new.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: zilisabethpangasch <zilisabethpangasch@      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 14:36:01 by zilisabethp   #+#    #+#                 */
/*   Updated: 2021/03/05 16:51:59 by zilisabethp   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"


/**
 * @tokenizer
 * Splits the input string into easier to handle tokens.
 * Puts the tokens into seperate list segments.
 * Returns a list with tokens terminated by a NULL pointer
 * Does not check whether it is valid.
*/

static int replace_env(char **in, int i, t_bucket *env)
{
	int		env_len;
	char	*ret;
	char	*substr;

	env_len = env_length(*in + i + 1);
	substr = ft_substr(*in, i + 1, env_len);
	ret = bucket_get_value(env, substr);
	free(substr);
	if (ret)
	{
		*in = easyjoin(ft_substr(*in, 0, i), ft_strdup(ret),
				 ft_strdup(*in + i+ env_len + 1));
		i += ft_strlen(ret);
	}
	else
	{
		*in = easyjoin(ft_substr(*in, 0, i - 1),
				 ft_strdup(*in + i + env_len +1), NULL);
	}
	return i;
}

void res_env(char **input, t_bucket *env)
{
	int		i;
	char	*in;
	char	*in_old;

	in = ft_strdup(*input);
	i = 0;
	while (in[i] && in[i] != '\n')
	{
		if (in[i] == '$')
		{
			in_old = in;
			replace_env(&in, i, env);
			free(in_old);
		}
		i++;
	}
	free(*input);
	*input = in;
}

t_token *tokenizer(char *in, t_bucket *env)
{
	t_token *token_l;

	res_env(&in, env);
	token_l = ft_calloc(1, sizeof(t_token));
	if (!token_l)
		ft_error("t_l head malloc went wrong", 27);
	get_token_list(&token_l, in);
	// ---------------
	while (token_l->next)
	{
		printf("[%s]\n", token_l->token);
		token_l = token_l->next;
	}
	// --------------- test
	return (token_l);
}
