/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_read_until_delimiter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 12:32:34 by tjans             #+#    #+#             */
/*   Updated: 2022/02/15 12:32:38 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * >INSERT POINT< [Binary] [Args] [read_until_delim]
 */

#include "io.h"
#include "builtins.h"

static t_token	*create_pipe_token(t_token *next, t_token *delim)
{
	t_token	*pipe;
	t_token *pipe_arg;

	pipe = ft_calloc(1, sizeof(t_token));
	pipe_arg = ft_calloc(1, sizeof(t_token));
	if (!pipe || !pipe_arg)
		ft_error("calloc", 6);
	pipe->token = ft_strdup("_reader");
	pipe->type = executable;
	pipe->result_type = BUILTIN;
	pipe->result.builtin = &builtin_reader;
	pipe->next = pipe_arg;
	pipe_arg->token = ft_strdup(delim->token);
	pipe_arg->type = non_special;
	pipe_arg->next = next;
	next->prev = pipe_arg;
	next->type = redirect_to_pipe;
	return (pipe);
}

t_token	*insert_pipe_token(t_token *delim, t_token *head)
{
	t_token	*insert_point;
	t_token	*new;

	insert_point = delim;
	while (insert_point->prev)
	{
		insert_point = insert_point->prev;
	}
	new = create_pipe_token(insert_point, delim);
	if (insert_point == head)
		return (new);
	return (head);
}

t_token	*replace_delims_with_pipes(t_token *head)
{
	t_token	*cur;

	cur = head;
	while (cur)
	{
		if (cur->type == read_until_delimiter)
		{
			head = insert_pipe_token(cur, head);
		}
		cur = cur->next;
	}
	return (head);
}
