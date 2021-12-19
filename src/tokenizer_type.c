/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_type.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:14:13 by zgargasc      #+#    #+#                 */
/*   Updated: 2021/12/18 17:14:14 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_tokens	tokenizer_identify(char *s)
{
	if (!*s)
		return (non_special);
	if (*s == '>')
	{
		if (*(s + 1) == '>')
			return (redirect_to_append);
		else
			return (redirect_to_overwrite);
	}
	if (*s == '<')
		return (redirect_from_file);
	if (*s == '|')
		return (redirect_to_pipe);
	return (non_special);
}
