/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: zilisabethpangasch <zilisabethpangasch@      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 14:36:01 by zilisabethp   #+#    #+#                 */
/*   Updated: 2021/03/30 16:20:39 by zilisabethp   ########   odam.nl         */
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
	token_l = ft_calloc(1, sizeof(t_token));
	if (!token_l)
		ft_error("t_l head malloc went wrong", 27);
	get_token_list(&token_l, in, 1);
	free(in);
	return (token_l);
}
