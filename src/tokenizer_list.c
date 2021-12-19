#include "minishell.h"
#include "tokenizer.h"

size_t get_whitespace_length(char *s)
{
	size_t	i;

	i = 0;
	while (iswhitespace(s[i]) && s[i] != '\n' && s[i])
		i++;
	return (i);
}

size_t	get_token_length(char *s)
{
	size_t	len;
	char	literal;

	len = 0;
	literal = 0;
	while (s[len] && s[len] != '\n')
	{
		if ((s[len] == '\'' || s[len] == '\"') && !literal)
			literal = s[len];
		else if ((s[len] == '\'' || s[len] == '\"') && literal == s[len])
		{
			literal = 0;
			if (!iswhitespace(s[len + 1]))
			{
				len++;
				continue ;
			}
		}
		len++;
		if (!s[len] || iswhitespace(s[len]))
			return (len);
	}
}

size_t	copy_str_to_token(char *dst, char *src, size_t len)
{
	size_t	dst_pos;
	size_t	src_pos;
	char	literal;

	dst_pos = 0;
	src_pos = 0;
	literal = 0;
	while (src_pos < len && src[src_pos] && !(!literal && iswhitespace(src[src_pos])))
	{
		if (src[src_pos] == '\'' || src[src_pos] == '\"')
		{
			if (literal == src[src_pos])
			{
				literal = 0;
				if (iswhitespace(src[src_pos + 1]))
					return (src_pos + 1);
			}
			else if (!literal)
				literal = src[src_pos];
			src_pos++;
		}
		dst[dst_pos] = src[src_pos];
		dst_pos++;
		src_pos++;
	}
	return (src_pos + 1);
}

size_t	get_next_token_str(char *in, char **dst)
{
	size_t start;
	size_t end;

	start = get_whitespace_length(in);
	end = get_token_length(in);
	*dst = ft_calloc(1, (end - start) * sizeof(char));
	if (!*dst)
		ft_error("calloc null", 12);
	return (copy_str_to_token(*dst, in + start, end - start));
}

t_token	*get_next_token(char **in)
{
	t_token	*token;
	size_t	token_len;
	size_t	in_len;

	in_len = ft_strlen(*in);
	if (!**in || *in == '\n')
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		ft_error("calloc in new_token error", 26);
	token_len = get_next_token_str(*in, &token->token);
	if (token_len < in_len)
		*in += token_len;
	else
		*in += in_len;
	return (token);
}

t_token *get_token_list(char *in)
{
	t_token *head;
	t_token	*cur;

	head = get_next_token(&in);
	cur = head;
	while (cur && *in)
	{
		cur->next = get_next_token(&in);
		cur = cur->next;
	}
	return (head);
}
