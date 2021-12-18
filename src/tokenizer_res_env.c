/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_res_env.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:14:11 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:14:35 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_ret(char **in, int i, struct s_state *state)
{
	char	*ret;

	ret = ft_itoa(state->ret);
	*in = easyjoin(ft_substr(*in, 0, i), ft_strdup(ret), \
		ft_strdup(*in + i + 2 + 1));
	i += ft_strlen(ret);
	return (i);
}

static int	replace_env(char **in, int i, struct s_state *state)
{
	int		env_len;
	char	*ret;
	char	*substr;

	env_len = env_length(*in + i + 1);
	substr = ft_substr(*in, i + 1, env_len);
	if (ft_strncmp(substr, "?", 2) == 0)
	{
		free(substr);
		return (get_ret(in, i, state));
	}
	ret = bucket_get_value(state->env->env, substr);
	free(substr);
	if (ret)
	{
		*in = easyjoin(ft_substr(*in, 0, i), ft_strdup(ret), \
				ft_strdup(*in + i + env_len + 1));
		i += ft_strlen(ret);
	}
	else
	{
		*in = easyjoin(ft_substr(*in, 0, i - 1),
				ft_strdup(*in + i + env_len + 1), NULL);
	}
	return (i);
}

void	res_env(char **input, struct s_state *state)
{
	int		i;
	char	*in;
	char	*in_old;
	int		is_literal;

	in = ft_strdup(*input);
	i = 0;
	is_literal = 0;
	while (in[i] && in[i] != '\n')
	{
		if (in[i] == '$' && !is_literal)
		{
			in_old = in;
			replace_env(&in, i, state);
			free(in_old);
		}
		if (in[i] == '\'')
			is_literal = !is_literal;
		i++;
	}
	free(*input);
	*input = in;
}
