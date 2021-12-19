#include "tokenizer.h"

t_tokens	tokenizer_identify(char *s)
{
	if (!*s)
		return (non_special);
	if (*s == '>')
	{
		if (*(s + 1) == '>')
			return (redirect_to_append);
		else
			return (redirect_to_overwrite);
	}
	if (*s == '<')
		return (redirect_from_file);
	if (*s == '|')
		return (redirect_to_pipe);
	return (non_special);
}
