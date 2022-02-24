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
		if (heredoc_reader(iterator))
			return (free_heredoc_list(list));
		iterator = iterator->next;
	}
	free_heredoc_list(list);
	return (0);
}