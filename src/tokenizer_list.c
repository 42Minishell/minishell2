// Created by Tom Jans on 16-03-21.

#include "minishell.h"
#include "tokenizer.h"

static int	find_next_token(char *in)
{
	int		i;

	i = 0;
	while (iswhitespace(in[i]) == true && in[i] != '\n' && in[i])
		i++;
	if (in[i] == '\n' || !in[i])
		return (-1);
	else
		return (i);
}

static int	find_end_token(char *in, t_tokens *type)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	if (in[i] == '\'' || in[i] == '\"')
	{
		c = in[i];
		i++;
	}
	while (in[i] && in[i] != '\n')
	{
		if (tokenizer_identify(in, &i, type))
			return (i);
		if (in[i] == c && c && (i != 0 && in[i - 1] != '\\'))
		{
			i++;
			break ;
		}
		if (!c && iswhitespace(in[i]) == true && (i != 0 && in[i - 1] != '\\'))
			break ;
		i++;
	}
	return (ternary_i((i == 0), -1, i));
}

static t_token	*new_token(void)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		ft_error("calloc in new_token error", 26);
	return (new);
}

static void	handle_special_token(t_token *current, t_tokens *type)
{
	if (*type != non_special)
	{
		current->type = *type;
		*type = non_special;
	}
}

void	get_token_list(t_token **token_l, char *in, t_tokens type)
{
	t_token	*current;
	int		i;
	int		j;

	current = *token_l;
	handle_special_token(current, &type);
	i = find_next_token(in);
	if (i < 0)
		return ;
	j = find_end_token(in + i, &type);
	if (j < 0)
		return ;
	current->token = strip_token(ft_substr(in, i,
		ternary_i((type == non_special), j, j - 1)));
	if (current->token == NULL)
		ft_error ("substr error in get_TL", 23);
	current->next = new_token();
	current = current->next;
	in = in + j + i;
	get_token_list(&current, in, type);
}
