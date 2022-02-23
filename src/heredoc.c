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

#include "heredoc.h"

int	process_heredocs(t_token *head)
{
	t_heredoc_list	*list;

	list = create_list_from_tokens(head);
	free_heredoc_list(list);
	return (0);
}