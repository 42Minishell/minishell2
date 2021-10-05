#include "tokenizer.h"

int	tokenizer_identify(char *s, int *i, t_tokens *type)
{
	if (!s[*i])
		return (0);
	if (s[*i] == ';')
		*type = executable;
	else if (s[*i] == '>' && s[*i + 1] == '>')
	{
		*type = redirect_to_append;
		(*i)++;
	}
	else if (s[*i] == '>')
		*type = redirect_to_overwrite;
	else if (s[*i] == '<')
		*type = redirect_from_file;
	else if (s[*i] == '|')
		*type = redirect_to_pipe;
	else
		return (0);
	(*i)++;
	return (1);
}
