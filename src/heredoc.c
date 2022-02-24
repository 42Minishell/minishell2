/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:12:02 by tjans             #+#    #+#             */
/*   Updated: 2022/02/23 18:12:03 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

static t_token	*create_redir_token(t_heredoc_list *heredoc, t_token *insert)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->token = ft_strdup(heredoc->fullpath);
	token->type = redirect_from_file_and_unlink;
	token->prev = insert;
	token->next = insert->next;
	if (token->next)
		token->next->prev = token;
	insert->next = token;
	return (token);
}

static void	insert_redir_token(t_heredoc_list *heredoc)
{
	t_token	*insert_point_after_args;

	insert_point_after_args = heredoc->insert_point;
	while (insert_point_after_args->next && \
		insert_point_after_args->next->type == non_special)
		insert_point_after_args = insert_point_after_args->next;
	create_redir_token(heredoc, insert_point_after_args);
}

int	process_heredocs(t_token *head)
{
	t_heredoc_list	*list;
	t_heredoc_list	*iterator;

	list = create_list_from_tokens(head);
	if (!list)
		return (0);
	iterator = list;
	while (iterator)
	{
		if (iterator->next && iterator->next->insert_point == \
			iterator->insert_point)
		{
			printf("Error: Multiple heredocs for one command.\n");
			return (free_heredoc_list(list, 1));
		}
		if (heredoc_reader(iterator))
			return (free_heredoc_list(list, 1));
		insert_redir_token(iterator);
		iterator = iterator->next;
	}
	return (free_heredoc_list(list, 0));
}
