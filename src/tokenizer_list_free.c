// Created by Tom Jans on 26-03-21.

#include "tokenizer.h"

void	tokenizer_list_free(t_token *head)
{
	t_token	*head_prev;

	while (head)
	{
		if (head->token)
			free(head->token);
		head_prev = head;
		head = head->next;
		free(head_prev);
	}
}
