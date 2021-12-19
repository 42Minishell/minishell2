/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zilisabethpangasch <zilisabethpangasch@      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 14:36:01 by zilisabethp   #+#    #+#                 */
/*   Updated: 2021/12/18 17:14:17 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strip_token(char *token)
{
	char	*new_token;

	if (*token != '\'' && *token != '"')
		return (token);
	new_token = ft_substr(token, 1, ft_strlen(token) - 2);
	free(token);
	return (new_token);
}

t_token	*tokenizer(char *in, t_state *state)
{
	t_token	*token_l;

	res_env(&in, state);
	token_l = get_token_list(in);
	free(in);
	return (token_l);
}
