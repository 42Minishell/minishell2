/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_len.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/05 15:00:09 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/01/05 15:00:10 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

size_t	get_whitespace_length(char *s)
{
	size_t	i;

	i = 0;
	while (iswhitespace(s[i]) && s[i] != '\n' && s[i])
		i++;
	return (i);
}

size_t	get_token_length(char *s)
{
	size_t	len;
	char	literal;

	len = 0;
	literal = 0;
	while (s[len] && s[len] != '\n')
	{
		if ((s[len] == '\'' || s[len] == '\"') && !literal)
			literal = s[len];
		else if ((s[len] == '\'' || s[len] == '\"') && literal == s[len])
		{
			literal = 0;
			if (!iswhitespace(s[len + 1]))
			{
				len++;
				continue ;
			}
		}
		len++;
		if (!s[len] || iswhitespace(s[len]))
			return (len);
	}
	return (len);
}
