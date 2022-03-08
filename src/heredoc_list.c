/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:31:30 by tjans             #+#    #+#             */
/*   Updated: 2022/02/23 18:31:31 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "heredoc.h"

static void	gen_filename(char *dst, char *token, int ptr)
{
	char	*ptrs;

	if (ptr < 0)
		ptr *= -1;
	ft_strlcpy(dst, "tmp_", 16);
	ft_strlcat(dst, token, 16);
	ptrs = ft_itoa((int)ptr);
	ft_strlcat(dst, ptrs, 16);
	free(ptrs);
}

static void	append_to_list(t_heredoc_list **head, t_token *insert, \
	t_token *delim)
{
	t_heredoc_list	*end;
	t_heredoc_list	*new;
	size_t			ptrint;

	new = ft_malloc(sizeof(t_heredoc_list));
	ptrint = (size_t)(insert);
	ptrint >>= 16;
	gen_filename(new->tmp_fn, insert->token, (int)ptrint);
	new->insert_point = insert;
	new->delim = ft_strdup(delim->token);
	new->next = NULL;
	if (*head)
	{
		end = *head;
		while (end->next)
			end = end->next;
		end->next = new;
	}
	else
		*head = new;
}

t_heredoc_list	*create_list_from_tokens(t_token *head)
{
	t_heredoc_list	*list;
	t_token			*insert;

	list = NULL;
	while (head)
	{
		if (head->type == executable || head->type == redirect_to_pipe)
			insert = head;
		else if (head->type == read_until_delimiter)
		{
			if (!insert)
				insert = head;
			while (insert && insert->type != executable && \
				insert->type != redirect_to_pipe)
				insert = insert->next;
			if (!insert)
				return (list);
			append_to_list(&list, insert, head);
			insert = NULL;
		}
		head = head->next;
	}
	return (list);
}

int	free_heredoc_list(t_heredoc_list *head, int err)
{
	t_heredoc_list	*prev;

	while (head)
	{
		prev = head;
		head = head->next;
		if (err)
			unlink(prev->fullpath);
		free(prev->delim);
		free(prev);
	}
	return (err);
}
