// Created by Tom Jans on 28-02-21.

#include "hashtable.h"

unsigned long	hash(char *str)
{
	unsigned long	hash;

	hash = 0;
	while (*str)
	{
		hash += *str;
		str++;
	}
	return (hash % HASHTABLE_SIZE);
}

static t_bucket	*bucket_get_overflow(t_bucket *bucket, char *key, int create)
{
	while (bucket)
	{
		if (strcmp(bucket->key, key) == 0)
		{
			if (create)
				free(key);
			return (bucket);
		}
		if (!bucket->next && create)
		{
			bucket->next = calloc(1, sizeof(t_bucket));
			bucket = bucket->next;
			bucket->key = key;
			return (bucket);
		}
		bucket = bucket->next;
	}
	return (NULL);
}

t_bucket	*bucket_get(t_bucket *table, char *key, int create)
{
	unsigned long	keyhash;
	t_bucket		*bucket;

	keyhash = hash(key);
	bucket = table + keyhash;
	if (bucket->key)
		return (bucket_get_overflow(bucket, key, create));
	else if (create)
	{
		bucket->key = key;
		return (bucket);
	}
	return (NULL);
}

char	*bucket_get_value(t_bucket *table, char *key)
{
	t_bucket	*bucket;

	bucket = bucket_get(table, key, 0);
	if (!bucket)
		return (NULL);
	return (bucket->value);
}
