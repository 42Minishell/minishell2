// Created by Tom Jans on 27-02-21.

#include "hashtable.h"
#include "minishell.h"

static void	bucket_overflow_free(t_bucket *bucket)
{
	t_bucket	*prev;

	while (bucket)
	{
		prev = bucket;
		bucket = bucket->next;
		free(prev->key);
		free(prev->value);
		free(prev);
	}
}

t_bucket	*bucket_new_table(void)
{
	t_bucket	*ptr;

	ptr = ft_calloc(HASHTABLE_SIZE, sizeof(t_bucket));
	return (ptr);
}

void	bucket_add(t_bucket *table, char *key, char *val)
{
	table = bucket_get(table, strdup(key), 1);
	if (table->value)
		free(table->value);
	table->value = ft_strdup(val);
	if (table->value == NULL)
		ft_error("MEMORY ERROR STRDUP", 20);
}

void	bucket_del(t_bucket *table, char *key)
{
	table = bucket_get(table, key, 0);
	if (table)
	{
		free(table->key);
		free(table->value);
		table->key = "";
	}
}

void	bucket_free_table(t_bucket *table)
{
	int	i;

	i = 0;
	while (i < HASHTABLE_SIZE)
	{
		if (table[i].key && *table[i].key)
		{
			free(table[i].key);
			free(table[i].value);
		}
		bucket_overflow_free(table[i].next);
		i++;
	}
	free(table);
}
