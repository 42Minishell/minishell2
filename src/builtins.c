// Created by Tom Jans on 05-03-21.

#include "builtins.h"

static void	set_table(t_function_lookup *entry, \
	char *key, void *func_ptr)
{
	entry->exec = key;
	entry->func_ptr = func_ptr;
}

static t_function_lookup	*get_table(void)
{
	t_function_lookup	*lookuptable;

	lookuptable = ft_calloc(5, sizeof(t_function_lookup));
	set_table(lookuptable, "unset", &builtin_unset);
	set_table(lookuptable + 1, "export", &builtin_export);
	set_table(lookuptable + 2, "echo", &builtin_echo);
	set_table(lookuptable + 3, "env", &builtin_export);
	return (lookuptable);
}

void	*find_builtin_func(char *exec)
{
	size_t				i;
	size_t				e_len;
	t_function_lookup	*table;

	i = 0;
	e_len = ft_strlen(exec);
	table = get_table();
	while (table[i].exec)
	{
		if (ft_strncmp(exec, table[i].exec, e_len + 1) == 0)
			return (table[i].func_ptr);
		i++;
	}
	return (NULL);
}
