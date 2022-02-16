/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjans <tnjans@outlook.de>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 14:36:01 by zilisabethp   #+  #+#    #+#             */
/*   Updated: 2022/02/16 11:32:57 by tjans            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"

const static t_lexer_action_lookup	g_lexer_table[6] = {
{' ', &lexer_action_whitespace},
{'>', &lexer_action_redirection_right},
{'<', &lexer_action_redirection_left},
{'|', &lexer_action_pipe},
{0, &lexer_action_non_special},
{0, NULL}
};

int	is_special_character(char c)
{
	int	i;

	i = 0;
	while (g_lexer_table[i].token)
	{
		if (g_lexer_table[i].token == c)
			return (1);
		i++;
	}
	return (0);
}

static int	get_tokens_from_str(char *in, t_token **head, t_state *state)
{
	int		i;
	t_token	*cur;

	cur = NULL;
	while (*in)
	{
		i = 0;
		while (g_lexer_table[i].action)
		{
			if (g_lexer_table[i].token == *in || !g_lexer_table[i].token)
			{
				if (g_lexer_table[i].action(&cur, &in, state))
					return (1);
				if (!*head && cur)
					*head = cur;
				if (cur && cur->next)
					cur = cur->next;
				break ;
			}
			i++;
		}
	}
	return (0);
}

t_token	*tokenizer(char *in, t_state *state)
{
	t_token	*head;

	(void)state;
	head = NULL;
	if (get_tokens_from_str(in, &head, state))
		printf("Syntax error.\n");
	free(in);
	return (head);
}
