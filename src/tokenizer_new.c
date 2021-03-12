/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer_new.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: zilisabethpangasch <zilisabethpangasch@      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/03 14:36:01 by zilisabethp   #+#    #+#                 */
/*   Updated: 2021/03/05 16:51:59 by zilisabethp   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenizer.h"


/**
 * @tokenizer
 * Splits the input string into easier to handle tokens.
 * Puts the tokens into seperate list segments.
 * Returns a list with tokens terminated by a NULL pointer
 * Does not check whether it is valid.
*/

int find_next_token(char *in)
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

int find_end_token(char *in)
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
			break;
		}
		if (c == non_special && iswhitespace(in[i]) == true && 
			(i != 0 && in[i - 1] != '\\'))
			break;
		i++;
	}
	if (i == 0)
		return (-1);
	return (i);
}

t_token *new_token()
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		ft_error("calloc in new_token error", 26);
	return (new);
}

void	get_token_list(t_token **token_l, char *in)
{
	t_token *current;
	int		i;
	int		j;

	current = *token_l;
	i = find_next_token(in);
	if (i < 0)
		return ;
	j = find_end_token(in + i);
	if (j < 0)
		return ;
	// ------------ test
	printf("[%i], [%i]\n", i , j);
	// -------------
	current->token = ft_substr(in, i, j);
	if (current->token == NULL)
		ft_error ("substr error in get_TL", 23);
	current->next = new_token();
	current = current->next;
	in = in + j + i;
	get_token_list(&current, in);
}

// puts all tokens into seperate nodes
// last node will be null
// Not checking for backslashes
// not checking for unequal amounts of quatation marks
// easily added.
// have to make a clean header still and norm.
// 

int env_length(char *in)
{
	int		i;

	i = 0;
	while (in[i] && iswhitespace(in[i]) != true && in[i] != '\n')
		i++;
	return (i);
}

void res_env(char **input, t_bucket *env)
{
	int		i;
	int		env_len;
	char	*in;
	char	*ret;

	in = ft_strdup(*input);
	i = 0;
	while (in[i] && in[i] != '\n')
	{
		if (in[i] == '$')
		{
			env_len = env_length(in + i + 1);
			ret = bucket_get_value(env, ft_substr(in,i + 1, env_len));
			if (ret)
			{
				in = easyjoin(ft_substr(in, 0, i), ft_strdup(ret),
							  ft_strdup(in +
										i + env_len + 1));
				i += ft_strlen(ret);
			}
			else
			{
				in = easyjoin(ft_substr(in, 0, i), ft_strdup(in + i + env_len
				), NULL);
			}
		}
		i++;
	}
	free(*input);
	*input = in;
}

t_token *tokenizer(char *in, t_bucket *env)
{
	t_token *token_l;

	res_env(&in, env);
	token_l = ft_calloc(1, sizeof(t_token));
	if (!token_l)
		ft_error("t_l head malloc went wrong", 27);
	get_token_list(&token_l, in);
	// ---------------
	while (token_l->next)
	{
		printf("[%s]\n", token_l->token);
		token_l = token_l->next;
	}
	// --------------- test
	return (token_l);
}
