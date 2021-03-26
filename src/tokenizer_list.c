// Created by Tom Jans on 16-03-21.

#include "minishell.h"
#include "tokenizer.h"

int	find_next_token(char *in)
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

int	find_end_token(char *in)
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
		if (in[i] == c && c != non_special && (i != 0 && in[i - 1] != '\\'))
		{
			i++;
			break ;
		}
		if (c == non_special && iswhitespace(in[i]) == true && \
			(i != 0 && in[i - 1] != '\\'))
			break ;
		i++;
	}
	if (i == 0)
		return (-1);
	return (i);
}

t_token	*new_token(void)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		ft_error("calloc in new_token error", 26);
	return (new);
}

void	get_token_list(t_token **token_l, char *in)
{
	t_token	*current;
	int		i;
	int		j;

	current = *token_l;
	i = find_next_token(in);
	if (i < 0)
		return ;
	j = find_end_token(in + i);
	if (j < 0)
		return ;
	current->token = strip_token(ft_substr(in, i, j));
	if (current->token == NULL)
		ft_error ("substr error in get_TL", 23);
	current->next = new_token();
	current = current->next;
	in = in + j + i;
	get_token_list(&current, in);
}