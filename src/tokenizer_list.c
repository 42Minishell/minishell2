/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_list.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: zgargasc <zgargasc@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/12/18 17:14:09 by zgargasc      #+#    #+#                 */
/*   Updated: 2022/01/05 14:59:43 by zgargasc      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

static size_t	get_next_token_str(char *in, char **dst, t_token_type *type)
{
	size_t	start;
	size_t	end;

	start = get_whitespace_length(in);
	end = get_token_length(in);
	*dst = ft_calloc(1, (end - start + 1) * sizeof(char));
	if (!*dst)
		ft_error("calloc null", 12);
	return (copy_str_to_token(*dst, in + start, end - start, type));
}

static t_token	*get_next_token(char **in, t_token_type *type)
{
	t_token	*token;
	size_t	token_len;
	size_t	in_len;

	in_len = ft_strlen(*in);
	if (!**in || **in == '\n')
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		ft_error("calloc in new_token error", 26);
	token->type = *type;
	token_len = get_next_token_str(*in, &token->token, type);
	if (**in == ' ')
		token_len++;
	if (token_len < in_len)
		*in += token_len;
	else
		*in += in_len;
	return (token);
}

static t_token	*clean_empty_token(t_token *prev, t_token *token)
{
	if (ft_strlen(token->token) == 0)
	{
		free(token->token);
		free(token);
		return (prev);
	}
	return (token);
}

t_token	*get_token_list(char *in)
{
	t_token			*head;
	t_token			*cur;
	t_token_type	next_type;

	next_type = executable;
	head = get_next_token(&in, &next_type);
	if (!head)
	{
		head = ft_calloc(1, sizeof(t_token));
		if (!head)
			ft_error("calloc err", 11);
	}
	cur = head;
	while (cur && *in)
	{
		cur->next = get_next_token(&in, &next_type);
		cur->next->prev = cur;
		cur = clean_empty_token(cur, cur->next);
	}
	cur->next = ft_calloc(1, sizeof(t_token));
	if (!cur->next)
		ft_error("calloc err", 11);
	return (head);
}
