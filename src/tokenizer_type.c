#include "tokenizer.h"

int	tokenizer_identify(char *s, int *i, t_tokens *type)
{
	if (s[*i] == ';')
		*type = executable;
	else
		return (0);
	(*i)++;
	return (1);
}
