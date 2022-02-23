/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:04:10 by tjans             #+#    #+#             */
/*   Updated: 2022/02/23 18:04:11 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef HEREDOC_H
# define HEREDOC_H
# include "tokenizer.h"

typedef struct s_heredoc_list
{
	char					tmp_fn[16];
	char					*delim;
	t_token					*insert_point;
	struct s_heredoc_list	*next;
}	t_heredoc_list;

int				process_heredocs(t_token *head);
t_heredoc_list	*create_list_from_tokens(t_token *head);
#endif
